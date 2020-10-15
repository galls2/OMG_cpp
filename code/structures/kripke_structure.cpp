//
// Created by galls2 on 29/09/19.
//

#include <utils/z3_utils.h>
#include <formulas/sat_solver.h>
#include <configuration/omg_config.h>
#include "kripke_structure.h"
#include <utils/Stats.h>
#include <utils/bdd_utils.h>

using namespace avy;

KripkeStructure::KripkeStructure(PropFormula tr, CtlFormula::PropertySet aps, const z3::expr &state_f,
        const z3::expr &init_f, const std::map<std::string, size_t>& ap_to_var_idx,  const std::map<z3::expr, size_t, Z3ExprComp>& var_mapping, Cudd& mgr)
: _transitions(std::move(tr)), _aps(std::move(aps)), _state_formula(state_f), _init_formula(init_f), _initial_states(BddUtils::expr_to_bdd(mgr, _init_formula, var_mapping)), _ap_to_var_idx(ap_to_var_idx)
{ }

size_t KripkeStructure::get_var_num_by_ap(const std::string &ap_text) const {
    if (_ap_to_var_idx.find(ap_text) == _ap_to_var_idx.end())
    {
        throw AtomicPropositionDoesNotExist(ap_text.data());
    }
    return _ap_to_var_idx.at(ap_text);
}

const CtlFormula::PropertySet &KripkeStructure::get_aps() const {
    return _aps;
}

const PropFormula &KripkeStructure::get_tr() const {
    return _transitions;
}

const z3::expr &KripkeStructure::get_state_formula() const {
    return _state_formula;
}
