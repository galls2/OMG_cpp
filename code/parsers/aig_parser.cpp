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
#include <utils/z3_utils.h>
#include <bits/unordered_map.h>
#include <formulas/sat_solver.h>
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
   //     std::cout << conversion_cmd << std::endl;
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


        _lit_formulas.insert(std::make_pair(0, _ctx.bool_val(false)));
        _lit_formulas.insert(std::make_pair(1, _ctx.bool_val(true)));
        for (auto lit : _in_literals)
            _lit_formulas.insert(std::make_pair(lit, _ctx.bool_const(std::to_string(lit).data())));
        for (auto lit : _prev_state_literals)
            _lit_formulas.insert(std::make_pair(lit, _ctx.bool_const(std::to_string(lit).data())));

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
                dfs(lines, formulas, first_line, target_lit - 1);
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


    std::unique_ptr<KripkeStructure> AigParser::to_kripke(const std::set<const CtlFormula*>& aps)
    {
        std::map<std::string, size_t> ap_to_var_idx;
        for (const auto &it : _ap_to_symb)
        {
            char ap_type = it.second[0];
            size_t raw_idx = std::stoul(it.second.substr(1));
            size_t idx = raw_idx + (ap_type == 'o' ? _metadata[AigMetadata::L] : 0);
            ap_to_var_idx.insert(std::make_pair(it.first, idx));
        }
        return std::make_unique<KripkeStructure>(*_tr_formula, aps, *_state_formula, *_init_formula, ap_to_var_idx);
    }

    void AigParser::calculate_tr_formula(const std::unordered_map<size_t, z3::expr> &formulas) {
        size_t new_var_index = (_metadata[AigMetadata::M] + 1) * 2 + 1;

        std::vector<z3::expr> prev_in, prev_latch, prev_out, next_in, next_latch, next_out;
        std::vector<std::reference_wrapper<std::vector<z3::expr>>>
                ins = {std::reference_wrapper<std::vector<z3::expr>>(prev_in),
                       std::reference_wrapper<std::vector<z3::expr>>(next_in)},
                latches = {std::reference_wrapper<std::vector<z3::expr>>(prev_latch),
                           std::reference_wrapper<std::vector<z3::expr>>(next_latch)},
                outs = {std::reference_wrapper<std::vector<z3::expr>>(prev_out),
                        std::reference_wrapper<std::vector<z3::expr>>(next_out)};

        generate_new_names(ins, new_var_index, _metadata[AigMetadata::I]);
        generate_new_names(latches, new_var_index, _metadata[AigMetadata::L]);
        generate_new_names(outs, new_var_index, _metadata[AigMetadata::O]);

        z3::expr_vector orig_in(_ctx), orig_ps(_ctx), orig_ns(_ctx), orig_out(_ctx);
        for (size_t i_lit : _in_literals) orig_in.push_back(_ctx.bool_const(std::to_string(i_lit).data()));
        for (size_t ps_lit : _prev_state_literals) orig_ps.push_back(_ctx.bool_const(std::to_string(ps_lit).data()));
        for (size_t ns_lit : _next_state_literals) orig_ns.push_back(_ctx.bool_const(std::to_string(ns_lit).data()));
        for (size_t o_lit : _out_literals) orig_out.push_back(_ctx.bool_const(std::to_string(o_lit).data()));

        generate_state_formula(formulas, prev_out, orig_in, orig_ps, orig_out, prev_in, prev_latch);

        z3::expr_vector ltr_parts(_ctx);
        for (size_t i = 0; i < _next_state_literals.size(); ++i) {
            auto &orig = const_cast<z3::expr &>(formulas.at(_next_state_literals[i]));
            z3::expr named_ltr_formula = orig.substitute(orig_in, vec_to_expr_vec(_ctx, prev_in))
                    .substitute(orig_ps, vec_to_expr_vec(_ctx, prev_latch));
            z3::expr constraint = next_latch[i] == named_ltr_formula;
            ltr_parts.push_back(constraint);
        }
        z3::expr ltr = z3::mk_and(ltr_parts);

        z3::expr state_next = _state_formula->substitute(vec_to_expr_vec(_ctx, prev_in), vec_to_expr_vec(_ctx, next_in))
                .substitute(vec_to_expr_vec(_ctx, prev_latch), vec_to_expr_vec(_ctx, next_latch))
                .substitute(vec_to_expr_vec(_ctx, prev_out), vec_to_expr_vec(_ctx, next_out));

        z3::expr_vector tr_parts(_ctx);
        tr_parts.push_back(ltr);
        tr_parts.push_back(*_state_formula);
        tr_parts.push_back(state_next);
        z3::expr tr_raw = z3::mk_and(tr_parts);

        z3::expr_vector ps(_ctx), ns(_ctx);
        for (const z3::expr &it : boost::join(prev_latch, prev_out)) ps.push_back(it);
        for (const z3::expr &it : boost::join(next_latch, next_out)) ns.push_back(it);

        std::map<std::string, z3::expr_vector> var_tags;
        var_tags.insert(std::make_pair(std::string("in0"), vec_to_expr_vec(_ctx, prev_in)));
        var_tags.insert(std::make_pair(std::string("in1"), vec_to_expr_vec(_ctx, next_in)));
        var_tags.insert(std::make_pair(std::string("ps"), ps));
        var_tags.insert(std::make_pair(std::string("ns"), ns));

        _tr_formula = std::make_unique<PropFormula>(tr_raw, var_tags);
    }

void
AigParser::generate_state_formula(const std::unordered_map<size_t, z3::expr> &formulas, std::vector<z3::expr> &prev_out,
                              const z3::expr_vector &orig_in, const z3::expr_vector &orig_ps,
                              const z3::expr_vector &orig_out, std::vector<z3::expr> &prev_in,
                              std::vector<z3::expr> &prev_latch) {
    z3::expr_vector state_formula_parts(_ctx);
    for (size_t o_lit : _out_literals)
    {
        z3::expr out_formula = _ctx.bool_const(std::to_string(o_lit).data()) == formulas.at(o_lit);
        z3::expr named_out_formula =
                out_formula.substitute(orig_in, vec_to_expr_vec(_ctx, prev_in))
                           .substitute(orig_ps, vec_to_expr_vec(_ctx, prev_latch)) // BUG?
                          .substitute(orig_out, vec_to_expr_vec(_ctx, prev_out));
        state_formula_parts.push_back(named_out_formula);
    }
    _state_formula = std::make_unique<z3::expr>(std::move(mk_and(state_formula_parts)));
}

void AigParser::extract_init(const std::vector<std::string> &file_lines) {
    z3::expr_vector ps_vars = _tr_formula->get_vars_by_tag(std::string("ps"));
    z3::expr_vector latch_values(_ctx);

    size_t first_line_idx = _metadata[AigMetadata::I] + 1;
    for (size_t i = first_line_idx ; i < first_line_idx + _metadata[AigMetadata::L]; ++i)
    {
        z3::expr var = ps_vars[i - first_line_idx];
        std::vector<std::string> parts;
        split(file_lines[i], ' ', parts);
  //      std::vector<z3::expr> v;
        if (parts.size() == 2)
        {
    //        v.push_back(var);
            latch_values.push_back(! var);
        }
        else
        {
            assert(parts.size() == 3);
            size_t init_val = std::stoul(parts[1]);
            if (init_val < 2)
            {
                assert (init_val == 1);
      //          v.push_back(!var);
                latch_values.push_back(var);
            }
            else
            {
                assert(init_val == 2*i);
          //      v.push_back(var);
        //        v.push_back(!var);
                latch_values.push_back(var);
            }
        }
  //      init_exprs.emplace_back(v);
    }

    z3::expr latch_constraints = z3::mk_and(latch_values);
//    assert(latch_values.size() == _metadata[AigMetadata::L]);
//    for (size_t j = _metadata[AigMetadata::L]; j < ps_vars.size(); ++j) latch_values.push_back(ps_vars[j]);
//    assert(latch_values.size() == _metadata[AigMetadata::L]+_metadata[AigMetadata::O]);

  //  _init_formula = std::make_unique<z3::expr>(_state_formula->substitute(ps_vars, latch_values).simplify());
    _init_formula = std::make_unique<z3::expr>(((*_state_formula) && latch_constraints).simplify());
   // std::cout << "INIT IN AIG-PARSER:: "<< _init_formula->to_string() << std::endl;
}

void AigParser::generate_new_names(std::vector<std::reference_wrapper<std::vector<z3::expr>>> &vec_of_vecs, size_t &start_from,
                                   size_t num_iters) {
    for (size_t i = 0; i < num_iters; ++i)
    {
        for (auto& vec : vec_of_vecs)
            vec.get().push_back(to_var(_ctx, ++start_from));
    }

}


