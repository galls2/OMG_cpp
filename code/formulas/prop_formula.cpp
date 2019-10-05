//
// Created by galls2 on 29/09/19.
//

#include "prop_formula.h"

std::vector<z3::expr> PropFormula::get_all_variables() const {
    std::vector<z3::expr> all_vars;
    for (const auto& vars_entry : _variables) {
        const z3::expr_vector &vars = vars_entry.second;
        for (size_t i = 0; i < vars.size(); ++i)
        {
            z3::expr var = vars[i];
            all_vars.push_back(var);
        }
    }
    return all_vars;
}
