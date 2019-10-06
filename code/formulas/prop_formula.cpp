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

const z3::expr_vector &PropFormula::get_vars_by_tag(const std::string& tag) const {
    return _variables.at(tag);
}

const std::map<std::string, z3::expr_vector> &PropFormula::get_variables_map() const {
    return _variables;
}


std::vector<z3::expr> PropFormula::get_vars_in_formula(z3::expr const & e) {
    std::vector<z3::expr> vars;
    if (e.is_app()) {
        unsigned num = e.num_args();
        for (unsigned i = 0; i < num; i++) {
            std::vector<z3::expr> sub_res = get_vars_in_formula(e.arg(i));
            vars.insert( vars.end(), sub_res.begin(), sub_res.end() );
        }

    }
//        else if (e.is_quantifier()) {
//            std::vector<z3::expr> sub_res = get_vars_in_formula(e.body());
//            vars.insert( vars.end(), sub_res.begin(), sub_res.end() );
//        }
    else {
        assert(e.is_var());
        vars.push_back(e);
        // do something
    }
    return vars;
}

