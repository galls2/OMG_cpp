
//
// Created by galls2 on 29/09/19.
//

#pragma once
#include <vector>
#include <z3++.h>
#include <utility>

typedef std::vector<z3::expr> VariableList;
typedef std::pair<VariableList, std::string> TaggedVariableList;

class PropFormula {
public:
    PropFormula(z3::expr& formula, std::vector<TaggedVariableList> variables) : _formula(formula), _variables(
            std::move(variables)) {}

    const z3::expr& get_formula() const { return _formula; }

    std::string to_string() const {
        return _formula.to_string();
    }


private:
    const z3::expr _formula;
    std::vector<TaggedVariableList> _variables;
};

