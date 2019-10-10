#pragma once

#include <set>
#include <utility>
#include <z3++.h>
#include <formulas/prop_formula.h>
#include <structures/concrete_state.h>
#include <utils/cartesian_product_generator.h>
class ConcreteState;

class KripkeStructure {
public:
    KripkeStructure(PropFormula tr, std::set<std::string> aps, z3::expr state_f, z3::expr init_f)
    : _transitions(std::move(tr)), _aps(std::move(aps)), _state_formula(state_f), _init_formula(init_f) {}
    const PropFormula& get_tr() const { return _transitions; }
    std::vector<ConcreteState> get_initial_states() const;
private:

    const PropFormula _transitions;
    const std::set<std::string> _aps;
    const z3::expr _state_formula;
    const z3::expr _init_formula;

};

