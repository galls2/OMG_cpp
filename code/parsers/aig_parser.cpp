#include <utility>

//
// Created by galls2 on 07/09/19.
//
#include <fstream>
#include <vector>
#include <iterator>
#include <iostream>
#include <cassert>
#include <regex>
#include <functional>
#include <boost/range/join.hpp>
#include <algorithm>
#include <utils/aiger-1.9.9/aiger.h>
#include <utils/string_utils.h>
#include <utils/version_manager.h>
#include "aig_parser.h"

AigParser::AigParser(const std::string &aig_path) : _aig_path(aig_path) {

    _aag_path = aig_to_aag(aig_path);

    std::vector<std::string> file_lines;
    read_aag(file_lines);

    extract_metadata(file_lines[0]);
    extract_ap_mapping(file_lines);
    extract_literals(file_lines);

    std::unordered_map<size_t, z3::expr> lit_formulas = calc_literal_formulas(file_lines);
    calculate_tr_formula(lit_formulas);
    extract_init(file_lines);


}
    AigParser &AigParser::extract_literals(const std::vector<std::string> &aag_lines) {
        for (size_t i = 1; i < 1 + _metadata[I]; ++i) {
            _in_literals.push_back(std::stoul(aag_lines[i]));
        }

        for (size_t i = _metadata[I] + 1; i < 1 + _metadata[L] + _metadata[I]; ++i) {
            std::array<std::string, 2> parts = split_to<2>(aag_lines[i], ' ');
            _prev_state_literals.push_back(std::stoul(parts[0]));
            _next_state_literals.push_back(std::stoul(parts[1]));
        }

        for (size_t i = _metadata[I] + _metadata[L] + 1; i < 1 + _metadata[L] + _metadata[O] + _metadata[I]; ++i) {
            _out_literals.push_back(std::stoul(aag_lines[i]));
        }

        return *this;
    }

    std::string AigParser::aig_to_aag(const std::string &aig_path) // change someday to something less disgusting
    {
        std::string PATH_TO_EXE = "/home/galls2/Desktop/OMG_cpp/code/utils/aiger-1.9.9/aigtoaig";
        std::string out_path = std::string(aig_path).replace(aig_path.length() - 2, 1, std::string("a"));
        std::string conversion_cmd = PATH_TO_EXE + " " + aig_path + " " + out_path;
        std::cout << conversion_cmd << std::endl;
        system(conversion_cmd.c_str());
        return out_path;
    }

    const AigParser &AigParser::read_aag(std::vector<std::string> &aag_container) const {
        std::string line;
        std::ifstream aag_file(_aag_path.c_str());
        while (std::getline(aag_file, line)) {
            aag_container.push_back(line);
        }

        return *this;
    }

    AigParser &AigParser::extract_metadata(const std::string &first_aag_line) {
        std::array<std::string, 6> components = split_to<6>(first_aag_line, ' ');
        assert(components[0] == std::string("aag"));
        _metadata[M] = std::stoul(components[1]);
        _metadata[I] = std::stoul(components[2]);
        _metadata[L] = std::stoul(components[3]);
        _metadata[O] = std::stoul(components[4]);
        _metadata[A] = std::stoul(components[5]);

        _first_and_literal = (_metadata.at(AigMetadata::I) + _metadata.at(L) + 1) * 2;

        return *this;
    }


    const std::unordered_map<AigMetadata, size_t, std::hash<size_t>> &AigParser::get_aig_metadata() {
        return _metadata;
    }

    AigParser &AigParser::extract_ap_mapping(const std::vector<std::string> &aag_lines) {
        size_t first_ap_index = 0;
        bool found_ap = false;

        const std::regex ap_line_regex("^[ilo][0-9].*");
        for (size_t i = 0; i < aag_lines.size(); ++i) {
            const std::string &aag_line = aag_lines[i];

            if (std::regex_match(aag_line, ap_line_regex)) {
                if (!found_ap) {
                    first_ap_index = i;
                    found_ap = true;
                }
                std::array<std::string, 2> parts = split_to<2>(aag_line, ' ');
                _ap_to_symb[parts[1]] = parts[0];
                _symb_to_ap[parts[0]] = parts[1];
            }
        }
        assert(found_ap);
        _first_ap_index = first_ap_index;
        return *this;
    }


    std::unordered_map<size_t, z3::expr> AigParser::calc_literal_formulas(const std::vector<std::string> &aag_lines) {


        _lit_formulas.insert(std::make_pair(0, _context.bool_val(false)));
        _lit_formulas.insert(std::make_pair(1, _context.bool_val(true)));
        for (auto lit : _in_literals)
            _lit_formulas.insert(std::make_pair(lit, _context.bool_const(std::to_string(lit).data())));
        for (auto lit : _prev_state_literals)
            _lit_formulas.insert(std::make_pair(lit, _context.bool_const(std::to_string(lit).data())));

        size_t first_and_line = _first_ap_index - _metadata[A];
        for (auto lit : _next_state_literals) dfs(aag_lines, _lit_formulas, first_and_line, lit);
        for (auto lit : _out_literals) dfs(aag_lines, _lit_formulas, first_and_line, lit);

//    for (auto it : _lit_formulas) std::cout << it.first << " ~ " << it.second << std::endl;

        return _lit_formulas;
    }

    const AigParser &
    AigParser::dfs(const std::vector<std::string> &lines, std::unordered_map<size_t, z3::expr> &formulas,
                   size_t first_line, size_t target_lit) const {
        if (formulas.find(target_lit) == formulas.end()) {
            if (target_lit % 2 == 1) {
                dfs(lines, formulas, first_line, target_lit - 1); // FOR NOW. DO OPT OF OR HERE!
                if (formulas.at(target_lit - 1).is_and()) {
                    const size_t and_line_index = first_line + (target_lit - _first_and_literal) / 2;
                    const std::string &and_line = lines[and_line_index];
                    std::array<std::string, 3> parts = split_to<3>(and_line, ' ');
                    size_t left_operand = std::stoul(parts[1]);
                    size_t right_operand = std::stoul(parts[2]);
                    if (left_operand % 2 == 1 && right_operand % 2 == 1) {
                        formulas.insert(std::make_pair(target_lit, formulas.at(left_operand - 1) ||
                                                                   formulas.at(right_operand - 1)));
                    } else {
                        formulas.insert(std::make_pair(target_lit, !formulas.at(target_lit - 1)));
                    }
                } else {
                    formulas.insert(std::make_pair(target_lit, !formulas.at(target_lit - 1)));
                }
            } else {
                const size_t and_line_index = first_line + (target_lit - _first_and_literal) / 2;
                const std::string &and_line = lines[and_line_index];
                std::array<std::string, 3> parts = split_to<3>(and_line, ' ');
                size_t left_operand = std::stoul(parts[1]);
                size_t right_operand = std::stoul(parts[2]);

                dfs(lines, formulas, first_line, left_operand);
                dfs(lines, formulas, first_line, right_operand);
                formulas.insert(std::make_pair(target_lit, formulas.at(left_operand) && formulas.at(right_operand)));
            }
        }
        return *this;
    }

    KripkeStructure AigParser::to_kripke(std::set<std::string> aps) {
        return KripkeStructure(*_tr_formula, std::move(aps), *_init_gen);
    }

    void AigParser::calculate_tr_formula(const std::unordered_map<size_t, z3::expr> &formulas) {
        const size_t max_var_index = (_metadata[AigMetadata::M] + 1) * 2;

        std::unordered_map<size_t, z3::expr> fresh_formulas;

        size_t new_var_index = max_var_index + 1;
        for (const auto &it : _in_literals) _fresh_literal_names[it] = ++new_var_index;
        size_t max_in_lit = new_var_index;
        for (const auto &it : _prev_state_literals) _fresh_literal_names[it] = ++new_var_index;
        size_t max_prev_lit = new_var_index;
        for (const auto &it : _next_state_literals) _fresh_literal_names[it] = ++new_var_index;
        size_t max_next_lit = new_var_index;
        for (const auto &it : _out_literals) _fresh_literal_names[it] = ++new_var_index;
        size_t max_out_lit = new_var_index;

        z3::expr_vector old_names(_context), new_names(_context);
        z3::expr_vector in(_context), out(_context), ps(_context), ns(_context);

        for (auto &fresh_literal_name : _fresh_literal_names) {
            z3::expr old_var = _context.bool_const(std::to_string(fresh_literal_name.first).data());
            old_names.push_back(old_var);

            std::string new_name = VersionManager::new_version(fresh_literal_name.second);
            z3::expr new_var = _context.bool_const(new_name.data());
            new_names.push_back(new_var);

            if (fresh_literal_name.second <= max_in_lit) in.push_back(new_var);
            else if (fresh_literal_name.second <= max_prev_lit) ps.push_back(new_var);
            else if (fresh_literal_name.second <= max_next_lit) ns.push_back(new_var);
            else {
                assert(fresh_literal_name.second <= max_out_lit);
                out.push_back(new_var);
            }
        };

        for (auto it : boost::join(_next_state_literals,_out_literals)) {
            auto &orig = const_cast<z3::expr&>(formulas.at(it));

            z3::expr new_formula = orig.substitute(old_names, new_names);
            fresh_formulas.insert(std::make_pair(it, new_formula));
        }

        z3::expr_vector tr_formula_parts(_context);
        for (auto it : boost::join(_next_state_literals, _out_literals)) {
            size_t fresh_lit = _fresh_literal_names[it];
            z3::expr tr_part = _context.bool_const(std::to_string(fresh_lit).data()) == fresh_formulas.at(it);
            tr_formula_parts.push_back(tr_part);
        }

        z3::expr and_result = z3::mk_and(tr_formula_parts);
        std::map<std::string, z3::expr_vector> var_tags =  { {"in", in}, {"ps", ps}, {"ns", ns}, {"out", out} };
        PropFormula tr(and_result, var_tags);
        _tr_formula = std::make_unique<PropFormula>(std::move(tr));
    }

void AigParser::extract_init(const std::vector<std::string> &file_lines) {
    std::vector<std::vector<z3::expr>> init_exprs;
    z3::expr_vector ps_vars = _tr_formula->get_vars_by_tag("ps");
    for (size_t i = 1; i < _metadata[AigMetadata::L] + 1; ++i)
    {
        z3::expr var = ps_vars[i];
        std::vector<std::string> parts;
        split(file_lines[i], ' ', parts);
        std::vector<z3::expr> v;
        if (parts.size() == 1) v.push_back(var);
        else
        {
            assert(parts.size() == 2);
            size_t init_val = std::stoul(parts[1]);
            if (init_val < 2)
            {
                assert (init_val == 1);
                v.push_back(!var);
            }
            else
            {
                assert(init_val == 2*i);
                v.push_back(var);
                v.push_back(!var);
            }
        }
        init_exprs.emplace_back(v);
    }
    _init_gen = std::make_unique<CartesianProductGenerator<z3::expr>>(init_exprs);
}
