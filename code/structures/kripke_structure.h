#pragma once

#include <set>
#include <utility>
#include <z3++.h>
#include <formulas/prop_formula.h>
#include <structures/concrete_state.h>
#include <temporal/ctl_formula.h>
#include <unordered_set>
#include <utils/omg_exception.h>
#include "concrete_set.h"

class ConcreteState;

DECLARE_OMG_EXCEPTION(AtomicPropositionDoesNotExist)

class Z3ExprComp;

class KripkeStructure {
public:
    KripkeStructure(PropFormula tr, CtlFormula::PropertySet aps, const z3::expr &state_f,
                    const z3::expr &init_f, const std::map<std::string, size_t>& ap_to_var_idx,  const std::map<z3::expr, size_t, Z3ExprComp>& var_mapping, Cudd& mgr);
    const PropFormula& get_tr() const;
    const z3::expr& get_state_formula() const;
    const ConcreteSet& get_initial_states() { return _initial_states; };
    size_t get_var_num_by_ap(const std::string& ap_text) const;
    const CtlFormula::PropertySet& get_aps() const;

private:

    const PropFormula _transitions;
    const CtlFormula::PropertySet _aps;
    const z3::expr _state_formula;
    const z3::expr _init_formula;
    const ConcreteSet _initial_states;
    const std::map<std::string, size_t> _ap_to_var_idx;

};

