//
// Created by galls2 on 04/10/19.
//

#include <cassert>
#include <formulas/sat_solver.h>
#include "concrete_state.h"

template <typename T>
std::set<T> vector_to_set(const std::vector<T>& vec)
{
    return std::set<T>(vec.begin(), vec.end());
}

ConcreteState::ConcreteState(const KripkeStructure& kripke, const z3::expr &conjunct)  : _kripke(kripke), _conjunct(conjunct)
{
    assert(vector_to_set(PropFormula::get_vars_in_formula(_conjunct)) == vector_to_set(_kripke.get_tr().get_vars_by_tag("ps")));
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
    const PropFormula ns_formula = PropFormula(ns_raw_formula, variables_map);

    ISatSolver sat_solver = Z3SatSolver(_kripke.get_tr().get_formula().ctx()); // TODO CHANGE ME TO A CONFIGURABLE SAT SOLVER
    std::vector<SatSolverResult> sat_results = sat_solver.all_sat(ns_formula, variables_map["ns"]);

}
