//
// Created by galls2 on 29/09/19.
//

#include "kripke_structure.h"



ConcreteState KripkeStructure::get_first_initial_state() {
    std::vector<z3::expr> init = _init_gen.get_initial();
    return literals_to_state(init);
}

std::experimental::optional<ConcreteState> KripkeStructure::get_next_initial_state() {
    std::experimental::optional<std::vector<z3::expr>> init = _init_gen.get_next();
    if (init) return literals_to_state(init.value());
    return std::experimental::optional<ConcreteState>();
}

ConcreteState KripkeStructure::literals_to_state(const std::vector<z3::expr>& literals) const {
    z3::expr_vector conj_parts(_transitions.get_formula().ctx());
    for (const auto& it : literals) conj_parts.push_back(it);
    return ConcreteState(*this, z3::mk_and(conj_parts));
}
