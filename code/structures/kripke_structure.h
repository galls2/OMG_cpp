#include <utility>

#pragma once

#include <set>
#include <utility>
#include <z3++.h>
#include <formulas/prop_formula.h>
#include <structures/concrete_state.h>
#include <utils/cartesian_product_generator.h>
#include <temporal/ctl_formula.h>
#include <unordered_set>

class ConcreteState;

class KripkeStructure {
public:
    KripkeStructure(PropFormula tr, std::unique_ptr<CtlFormula::PropertySet> aps, const z3::expr &state_f, const z3::expr &init_f);
    const PropFormula& get_tr() const { return _transitions; }
    std::vector<ConcreteState> get_initial_states() const;
private:

    const PropFormula _transitions;
    const std::unique_ptr<CtlFormula::PropertySet> _aps;
    const z3::expr _state_formula;
    const z3::expr _init_formula;

};

