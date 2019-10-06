
//
// Created by galls2 on 29/09/19.
//

#pragma once
#include <vector>
#include <z3++.h>
#include <utility>
#include <unordered_map>
#include <map>
#include <cassert>


class PropFormula {
public:
    PropFormula(z3::expr& formula, const std::map<std::string, z3::expr_vector> &variables) : _formula(formula), _variables(
            variables) {}

    const z3::expr& get_formula() const { return _formula; }

    std::string to_string() const {
        return _formula.to_string();
    }

    const z3::expr_vector& get_vars_by_tag(const std::string& tag) const;
    std::vector<z3::expr> get_all_variables() const;

    static std::vector<z3::expr> get_vars_in_formula(z3::expr const & e);

    const std::map<std::string, z3::expr_vector> & get_variables_map() const;

private:
    const z3::expr _formula;
    const std::map<std::string, z3::expr_vector> & _variables;

};


