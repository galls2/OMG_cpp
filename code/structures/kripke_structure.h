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
#include <utils/omg_exception.h>

class ConcreteState;

DECLARE_OMG_EXCEPTION(AtomicPropositionDoesNotExist)

class KripkeStructure {
public:
    KripkeStructure(PropFormula tr, std::set<const CtlFormula*> aps, const z3::expr &state_f, const z3::expr &init_f,
            const std::map<std::string, std::size_t>& ap_to_var_idx);
    const PropFormula& get_tr() const { return _transitions; }
    std::vector<ConcreteState> get_initial_states() const;
    size_t get_var_num_by_ap(const std::string& ap_text) const;
    const std::set<const CtlFormula*>& get_aps() const;
private:

    const PropFormula _transitions;
    const std::set<const CtlFormula*> _aps;
    const z3::expr _state_formula;
    const z3::expr _init_formula;
    const std::map<std::string, size_t> _ap_to_var_idx;

};

