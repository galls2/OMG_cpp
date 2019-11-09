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
    z3::context& ctx = raw_tr.ctx();

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
        z3::expr conj = FormulaUtils::get_conj_from_sat_result(ctx, ns_vars, res);
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
#endif

bool ConcreteState::is_labeled_with(const std::string &ap) const {
    size_t var_idx = _kripke.get_var_num_by_ap(ap);
    const z3::expr_vector& state_vars = _kripke.get_tr().get_vars_by_tag("ps");
    z3::expr conj_with_var = _conjunct && state_vars[var_idx];

    z3::solver solver(state_vars.ctx());

    solver.add(conj_with_var);
    bool res = solver.check() == z3::sat;
    return res;
}

void ConcreteState::aps_by_sat(CtlFormula::PropertySet& pos, CtlFormula::PropertySet& neg) const
{
    z3::context& ctx = _kripke.get_tr().get_formula().ctx();
    z3::solver solver(ctx);

    solver.add(_conjunct);
    assert(solver.check() == z3::sat);
    z3::model m = solver.get_model();

    z3::expr_vector ps_vars = _kripke.get_tr().get_vars_by_tag("ps");
    const auto& aps = _kripke.get_aps();
    for (const CtlFormula* ap : aps)
    {
        size_t var_idx = _kripke.get_var_num_by_ap(ap->get_data());
        const z3::expr var = ps_vars[var_idx];
        if (z3::eq(m.eval(var), ctx.bool_val(true)))
            pos.emplace(ap);
        else
            neg.emplace(ap);
    }
}

PropFormula ConcreteState::get_bis0_formula() const {
    z3::context& ctx = _kripke.get_tr().get_formula().ctx();
    z3::expr_vector bis0_parts(ctx);
    z3::solver solver(ctx);

    solver.add(_conjunct);
    assert(solver.check() == z3::sat);
    z3::model m = solver.get_model();

    z3::expr_vector ps_vars = _kripke.get_tr().get_vars_by_tag("ps");
    for (const CtlFormula* ap : _kripke.get_aps())
    {
        size_t var_idx = _kripke.get_var_num_by_ap(ap->get_data());
        const z3::expr var = ps_vars[var_idx];
        if (z3::eq(m.eval(var), ctx.bool_val(true)))
            bis0_parts.push_back(var);
        else
            bis0_parts.push_back(!var);
    }
    z3::expr raw_bis0 = z3::mk_and(bis0_parts);
    PropFormula bis0(raw_bis0, {{"ps", ps_vars}});
    return bis0;
}

std::set<std::string> ConcreteState::string_sat_aps() const {
    std::set<std::string> sat_strs;
    z3::context& ctx = _kripke.get_tr().get_formula().ctx();
    z3::solver solver(ctx);

    solver.add(_conjunct);
    assert(solver.check() == z3::sat);
    z3::model m = solver.get_model();

    z3::expr_vector ps_vars = _kripke.get_tr().get_vars_by_tag("ps");
    for (const CtlFormula* ap : _kripke.get_aps())
    {
        size_t var_idx = _kripke.get_var_num_by_ap(ap->get_data());
        const z3::expr var = ps_vars[var_idx];
        if (z3::eq(m.eval(var), ctx.bool_val(true)))
            sat_strs.insert(ap->get_data());
    }
    return sat_strs;
}

bool ConcreteState::operator==(const ConcreteState &other) const {
    return z3::eq(other._conjunct, _conjunct);
}
