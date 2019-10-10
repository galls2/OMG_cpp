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
    KripkeStructure(PropFormula tr, std::set<std::string> aps, const z3::expr& init, const z3::expr& state_formula, const z3::expr& init)
    : _transitions(std::move(tr)), _aps(std::move(aps)), _state_formula(state_formula), _init_formula(init_formula) {}
    const PropFormula& get_tr() const { return _transitions; }
    std::vector<ConcreteState> get_initial_states() const;
private:
    ConcreteState literals_to_state(const std::vector<z3::expr>& literals) const;

    const PropFormula _transitions;
    const std::set<std::string> _aps;
    const z3::expr _state_formula;
    const z3::expr _init_formula;

};

