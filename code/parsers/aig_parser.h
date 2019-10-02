//
// Created by galls2 on 07/09/19.
//
#pragma once
#include <unordered_map>
#include <map>
#include <vector>
#include <array>
#include <string>
#include <z3++.h>
#include <experimental/optional>
#include <structures/kripke_structure.h>
#include <memory>

enum AigMetadata{
    M = 0, I = 1, L = 2, O = 3, A = 4
};


class AigParser {
public:

    explicit AigParser(const std::string& aig_path);
    const std::unordered_map<AigMetadata, size_t, std::hash<size_t>>& get_aig_metadata();
    KripkeStructure to_kripke(std::set<std::string> aps);
    ~AigParser() = default;



private:
    std::string aig_to_aag(const std::string& aig_path0);
    const AigParser& read_aag(std::vector<std::string>& aag_container) const;
    AigParser& extract_metadata(const std::string& first_aag_line);
    AigParser& extract_literals(const std::vector<std::string>& aag_lines);
    const AigParser& dfs(const std::vector<std::string> &lines, std::unordered_map<size_t, z3::expr>& formulas, size_t first_line, size_t target_lit) const;
    AigParser& extract_ap_mapping(const std::vector<std::string>& vector);
    std::unordered_map<size_t, z3::expr> calc_literal_formulas(const std::vector<std::string>& aag_lines);
    void calculate_tr_formula(const std::unordered_map<size_t, z3::expr>& fresh_formulas);


    const std::string _aig_path;
    std::string _aag_path;
    size_t _first_ap_index;
    size_t _first_and_literal;
    std::unordered_map<AigMetadata, size_t, std::hash<size_t>> _metadata;
    std::unordered_map<std::string, std::string> _ap_to_symb;
    std::unordered_map<std::string, std::string> _symb_to_ap;

    std::vector<size_t> _in_literals;
    std::vector<size_t> _out_literals;
    std::vector<size_t> _prev_state_literals;
    std::vector<size_t> _next_state_literals;
    std::unordered_map<size_t, z3::expr> _lit_formulas;
    z3::context _context;
    std::map<size_t, size_t> _fresh_literal_names;
    std::unique_ptr<PropFormula> _tr_formula;
};
