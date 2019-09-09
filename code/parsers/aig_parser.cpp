//
// Created by galls2 on 07/09/19.
//
#include <fstream>
#include <vector>
#include <iostream>
#include <cassert>
#include <regex>
#include "../utils/aiger-1.9.9/aiger.h"
#include "../utils/string_utils.h"

#include "aig_parser.h"


AigParser::AigParser(const std::string &aig_path) : _aig_path(aig_path)
{
  _aag_path = aig_to_aag(aig_path);

  std::vector<std::string> file_lines;
  read_aag(file_lines);

  extract_metadata(file_lines[0]);

  extract_ap_mapping(file_lines);

   extract_literals(file_lines);

  std::map<size_t, z3::expr> lit_formulas = get_literal_formulas();

  std::cout << _metadata[AigMetadata::M] << " " << _metadata[AigMetadata::I]<< std::endl;
}

void AigParser::extract_literals(const std::vector<std::string>& aag_lines)
{
    for (size_t i = 1; i < 1 + _metadata[I]; ++i)
    {
        std::vector<std::string> parts;
        split(aag_lines[i], ' ', parts);
        _in_literals.push_back(std::stoul(parts[0]));
    }

    for (size_t i = _metadata[I] + 1; i < 1 + _metadata[L] + _metadata[I]; ++i)
    {
        std::vector<std::string> parts;
        split(aag_lines[i], ' ', parts);
        _prev_state_literals.push_back(std::stoul(parts[0]));
        _prev_state_literals.push_back(std::stoul(parts[1]));
    }

    for (size_t i = _metadata[I] + _metadata[L] + 1; i < 1 + _metadata[L] + _metadata[O] + _metadata[I]; ++i)
    {
        std::vector<std::string> parts;
        split(aag_lines[i], ' ', parts);
        _out_literals.push_back(std::stoul(parts[0]));
    }
}

std::string AigParser::aig_to_aag(const std::string& aig_path) // change someday to something less disgusting
{
  std::string PATH_TO_EXE = "/home/galls2/Desktop/OMG_cpp/code/utils/aiger-1.9.9/aigtoaig";
  std::string out_path = std::string(aig_path).replace(aig_path.length()-2, 1, std::string("a"));
  std::string conversion_cmd = PATH_TO_EXE + " " + aig_path + " " + out_path;
  std::cout << conversion_cmd << std::endl;
  system(conversion_cmd.c_str());
  return out_path;
}

void AigParser::read_aag(std::vector<std::string>& aag_container) const
{
    std::string line;
    std::ifstream aag_file(_aag_path.c_str());
    while (std::getline(aag_file, line))
    {
      aag_container.push_back(line);
    }
}

void AigParser::extract_metadata(const std::string& first_aag_line)
{
    std::vector<std::string> components;
    split(first_aag_line, ' ', components);
    assert(components[0] == std::string("aag"));
    _metadata[M] = std::stoul(components[1]);
    _metadata[I] = std::stoul(components[2]);
    _metadata[L] = std::stoul(components[3]);
    _metadata[O] = std::stoul(components[4]);
    _metadata[A] = std::stoul(components[5]);
}



const std::map<AigMetadata, size_t> &AigParser::get_aig_metadata()
{
    return _metadata;
}

void AigParser::extract_ap_mapping(const std::vector<std::string>& aag_lines)
{
    size_t first_ap_index = 0;
    bool found_ap = false;

    const std::regex ap_line_regex("^[ilo][0-9].*");
    for (size_t i = 0; i < aag_lines.size(); ++i)
    {
        const std::string& aag_line = aag_lines[i];

        if (std::regex_match(aag_line, ap_line_regex))
        {
            if (!found_ap) { first_ap_index = i; found_ap = true; }
            std::vector<std::string> parts;
            split(aag_line, ' ', parts);
            _ap_to_symb[parts[1]] = parts[0];
            _symb_to_ap[parts[0]] = parts[1];
        }
    }
    assert(found_ap);
    _first_ap_index = first_ap_index;
}


std::map<size_t, z3::expr> AigParser::get_literal_formulas(const std::vector<std::string> &aag_lines)
{
    std::map<size_t, z3::expr> formulas;
    z3::context c;

    formulas[0] = c.bool_val(false);
    formulas[1] = c.bool_val(true);
    for (auto lit : _in_literals) formulas[lit] = c.bool_const(std::to_string(lit));
    for (auto lit : _prev_state_literals) formulas[lit] = c.bool_const(std::to_string(lit));

    size_t first_and_line = _first_ap_index - _metadata[A];
    for (auto lit : _next_state_literals) dfs(aag_lines, first_and_line, lit);
    for (auto lit : _out_literals) dfs(aag_lines, first_and_line, lit);

}

void AigParser::dfs(const std::vector<std::string> &lines, std::map<size_t, z3::expr>& formulas, size_t first_line, size_t target_lit) {
    auto it = formulas.find(target_lit);
    if (it != formulas.end()) return it->second;

    if (target_lit % 2 == 1) {
        dfs(lines, formulas, first_line, target_lit - 1); // FOR NOW. DO OPT OF OR HERE!
        formulas[target_lit] = !formulas[target_lit - 1];
    } else {
        const std::string &and_line = lines[target_lit];
        std::vector<std::string> parts;
        split(and_line, ' ', parts);
        size_t left_operand = std::stoul(parts[1]);
        size_t right_operand = std::stoul(parts[2]);

        dfs(lines, formulas, first_line, left_operand);
        dfs(lines, formulas, first_line, right_operand);
        formulas[target_lit] = formulas[left_operand] && formulas[right_operand];
    }
}
