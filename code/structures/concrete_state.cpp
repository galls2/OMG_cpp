//
// Created by galls2 on 04/10/19.
//

#include <cassert>
#include <formulas/sat_solver.h>
#include <utils/z3_utils.h>
#include <memory>
#include "concrete_state.h"
#include <algorithm>


ConcreteState::ConcreteState(const KripkeStructure& kripke, z3::expr conjunct)  : _kripke(kripke), _conjunct(conjunct)
{
#ifndef DEBUG
    std::vector<z3::expr> conj_vars = PropFormula::get_vars_in_formula(_conjunct);
    std::set<z3::expr, Z3ExprComp> conj_vars_set(conj_vars.begin(), conj_vars.end());
    std::set<z3::expr, Z3ExprComp> tr_ps_vars = expr_vector_to_set(_kripke.get_tr().get_vars_by_tag("ps"));
//    for (const auto & it : conj_vars_set) std::cout << it << std::endl;
//    std::cout << "^^^^^^^^^" << std::endl;
//    for (const auto & it : tr_ps_vars) std::cout << it << std::endl;
//    std::cout << "^^^^^^^^^" << std::endl;

    assert(conj_vars_set.size()  == tr_ps_vars.size());
    for (const auto & it : conj_vars_set) {
        bool found = false;
        for (const auto &it2 : tr_ps_vars)
            if (z3::eq(it, it2)) found = true;
        assert(found);
    }
#endif
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
        z3::expr named_conj = conj.substitute(tr.get_vars_by_tag("ns"), tr.get_vars_by_tag("ps"));
        ConcreteState cstate(_kripke, named_conj);
        successors.push_back(cstate);
    }
    _successors.emplace(successors);
}

std::ostream& operator<< (std::ostream& stream, const ConcreteState& concrete_state) {
    stream << concrete_state._conjunct.to_string();
    return stream;
}


#ifndef DEBUG
std::vector<bool> ConcreteState::to_bitvec() const
{
    z3::expr_vector vars = _kripke.get_tr().get_vars_by_tag("ps");
    z3::solver solver(_kripke.get_tr().get_formula().ctx());
    std::vector<bool> bits;
    for (size_t i = 0; i<vars.size();++i)
    {
        solver.reset();
        solver.add(_conjunct && vars[i]);
        bool res = solver.check() == z3::sat;
        bits.push_back(res);
    }
    return bits;

}

bool ConcreteState::is_labeled_with(const std::string &ap) const {
    size_t var_idx = _kripke.get_var_num_by_ap(ap);
    const z3::expr_vector& state_vars = _kripke.get_tr().get_vars_by_tag("ps");
    z3::expr conj_with_var = _conjunct && state_vars[var_idx];

    z3::solver solver(state_vars.ctx());

    solver.add(conj_with_var);
    bool res = solver.check() == z3::sat;
    return res;
}

#endif
