#pragma once
//
// Created by galls2 on 27/09/19.
//

#include <string>
#include <vector>
#include <temporal/ctl_formula.h>
#include <utility>

struct FormulaChunk {
    explicit FormulaChunk(bool expected_result=false) : _expected_result(expected_result) {}
    FormulaChunk& set_expected_result(bool expected_result) { _expected_result = expected_result; return *this; }
    bool get_expected_result() const { return _expected_result; }
    const std::vector<std::unique_ptr<CtlFormula>>& get_formulas() const { return _formulas; }
    FormulaChunk& add_formula(std::unique_ptr<CtlFormula> formula) { _formulas.emplace_back(std::move(formula)); return *this;}
private:
    std::vector<std::unique_ptr<CtlFormula>> _formulas;
    bool _expected_result;
};

class CtlFileParser {
public:
    typedef std::string RawFormula;
    typedef std::vector<std::string> RawFormulaChunk;


    // chunks is an out param
    bool parse_ctl_file(const std::string& file_path, std::vector<FormulaChunk>& formula_chunks) const;
private:
    FormulaChunk parse_raw_formula_chunk(const RawFormulaChunk& raw_formula_chunk) const;
};
