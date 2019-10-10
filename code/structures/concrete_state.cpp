//
// Created by galls2 on 04/10/19.
//

#include <cassert>
#include <formulas/sat_solver.h>
#include <utils/z3_utils.h>
#include <memory>
#include "concrete_state.h"



ConcreteState::ConcreteState(const KripkeStructure& kripke, z3::expr conjunct)  : _kripke(kripke), _conjunct(std::move(conjunct))
{
    assert(vector_to_set<z3::expr>(PropFormula::get_vars_in_formula(_conjunct)) == expr_vector_to_set(_kripke.get_tr().get_vars_by_tag("ps")));
}

std::vector<ConcreteState> ConcreteState::get_successors() {
    if (!_successors) compute_successors();
    return _successors.value();
}

void ConcreteState::compute_successors() {
    const PropFormula& tr = _kripke.get_tr();

    const z3::expr& raw_tr = tr.get_formula();
    const z3::expr ns_raw_formula = _conjunct && raw_tr;
    const std::map<std::string, z3::expr_vector> & variables_map = tr.get_variables_map();
    PropFormula ns_formula = PropFormula(ns_raw_formula, variables_map);

    std::unique_ptr<ISatSolver> sat_solver = std::make_unique<Z3SatSolver>(_kripke.get_tr().get_formula().ctx()); // TODO CHANGE ME TO A CONFIGURABLE SAT SOLVER
    z3::expr_vector ns_vars = variables_map.at(std::string("ns"));
    std::vector<SatSolverResult> sat_results = sat_solver->all_sat(ns_formula, expr_vector_to_vector(ns_vars));
    std::vector<ConcreteState> successors;
    for (const auto& res : sat_results)
    {
        assert(res.get_is_sat());
        z3::expr_vector lits(raw_tr.ctx());
        for (size_t i = 0; i < ns_vars.size(); ++i) {
            z3::expr var = ns_vars[i];
            lits.push_back(res.get_value(var) == SatResult::TRUE ? var : !var);
        }
        z3::expr conj = z3::mk_and(lits);
        ConcreteState cstate(_kripke, conj);
        successors.push_back(cstate);
    }
    _successors.emplace(successors);
}

std::ostream& operator<< (std::ostream& stream, const ConcreteState& concrete_state) {
    stream << concrete_state._conjunct.to_string();
    return stream;
}