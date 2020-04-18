//
// Created by galls2 on 05/10/19.
//

#include <z3.h>
#include <algorithm>
#include <cmath>
#include <set>
#include <utils/z3_utils.h>
#include "sat_solver.h"

SatSolverResult Z3SatSolver::solve_sat(const PropFormula &formula) {
    const z3::expr& raw_formula = formula.get_raw_formula();
    _solver.add(raw_formula);
    z3::check_result sat_res = _solver.check();
    if (sat_res == z3::unsat) return SatSolverResult();
    else if (sat_res == z3::sat) return SatSolverResult(_solver.get_model(), formula.get_all_variables());
    else { assert(sat_res == z3::unknown); throw SatSolverResultException("SAT result is unknown"); }
}

std::vector<SatSolverResult> Z3SatSolver::all_sat(const PropFormula &formula, const std::vector<z3::expr>& vars, bool complete_assignments = false ) {
    std::vector<SatSolverResult> assignments;
    const z3::expr &raw_formula = formula.get_raw_formula();
    z3::solver solver(raw_formula.ctx());

    solver.add(raw_formula);
    while (solver.check() == z3::sat)
    {
        z3::model m = solver.get_model();
        SatSolverResult res(m, vars);
        add_assignments(assignments ,res, vars, complete_assignments);
        z3::expr blocking_clause = get_blocking_clause(m, vars);
        solver.add(blocking_clause);
    }
    return assignments;
}

z3::expr Z3SatSolver::get_blocking_clause(const z3::model& model, const std::vector<z3::expr> &var_vector) {
    z3::context& ctx = model.ctx();
    z3::expr_vector literals(ctx);
    for (const z3::expr& var : var_vector)
    {
        literals.push_back(z3::eq(model.eval(var), ctx.bool_val(true)) ? (!var) : (var));
    }
    return z3::mk_or(literals);
}

void Z3SatSolver::add_assignments(std::vector<SatSolverResult> &assignemnts, SatSolverResult result,
                                  const std::vector<z3::expr> &vars, bool complete_assignment) {
    assert(result.get_is_sat());
    if (!complete_assignment) {
        assignemnts.push_back(result);
        return;
    }
    else
    {
        std::set<size_t> undef_idxs;
        for (size_t i = 0; i < vars.size(); ++i) if (result.get_value(vars[i]) == SatResult::UNDEF) undef_idxs.insert(i);
        for (size_t i = 0; i < (1 << undef_idxs.size()); ++i)
        {
            std::map<z3::expr, SatResult, Z3ExprComp> vals;
            for (size_t j = 0; j < vars.size(); ++j)
            {
                if (undef_idxs.find(j) == undef_idxs.end())

                    vals.emplace(vars[j], result.get_value(vars[j]));
                else
                {
                    vals.emplace(vars[j], SatResult::TRUE);
                    vals.emplace(vars[j], SatResult::FALSE);
                }
            }
            assignemnts.emplace_back(std::move(vals));
        }
    }
}

std::pair<int, SatSolverResult> Z3SatSolver::inc_solve_sat(const PropFormula& formula, const std::vector<z3::expr>& flags) {
    const z3::expr &raw_formula = formula.get_raw_formula();
    _solver.add(raw_formula);

    z3::expr_vector assumptions(raw_formula.ctx());

    for (size_t i = 0; i < flags.size(); ++i) {
        assumptions.push_back(flags[i]);
        if (_solver.check(assumptions))
            return {i, SatSolverResult(_solver.get_model(), formula.get_all_variables())};
        assumptions.pop_back();
    }
    return {-1, SatSolverResult()};
}

z3::expr_vector Z3SatSolver::get_unsat_core(const PropFormula& formula, z3::expr_vector& assumptions)
{
    const z3::expr& raw_formula = formula.get_raw_formula();
    _solver.add(raw_formula);
    z3::check_result sat_res = _solver.check(assumptions);
    assert(sat_res == z3::check_result::unsat);

    //   std::cout << _solver.check(assumptions) << std::endl;
    z3::expr_vector unsat_core = _solver.unsat_core();
    return unsat_core;
}

bool Z3SatSolver::is_sat(const z3::expr &raw_formula) {
    _solver.add(raw_formula);
    z3::check_result sat_res = _solver.check();
    if (sat_res == z3::unsat) return false;
    else if (sat_res == z3::sat) return true;
    else { assert(sat_res == z3::unknown); throw SatSolverResultException("SAT result is unknown"); }
}


SatSolverResult::SatSolverResult() : _is_sat(false) { }

SatSolverResult::SatSolverResult(const z3::model& model, const std::vector<z3::expr>& vars) : _is_sat(true)
{
    auto& context = model.ctx();
    for (const auto& var : vars)
    {
        SatResult var_value = Z3_val_to_sat_result(model.eval(var).bool_value());
        _values.emplace(var, var_value);
    }
}

SatSolverResult::SatSolverResult(const std::map<z3::expr, Z3_lbool> &values) : _is_sat(true)
{
    for (const auto& it : values)
        _values.emplace(it.first, Z3_val_to_sat_result(it.second));
}


SatResult SatSolverResult::get_value(const z3::expr& var ) const {
    if (!_is_sat) throw SatSolverResultException("Formula is unsat");
    if (_values.find(var) != _values.end())
        return  _values.at(var);

    else throw SatSolverResultException("Variables not in assignment");


}

z3::expr SatSolverResult::to_conjunt(z3::context& ctx) const {
    z3::expr_vector lits(ctx);
    for (const auto & value : _values) {
        if (value.second != SatResult::UNDEF)
            lits.push_back(value.second == SatResult::TRUE ? (value.first) : (!value.first));
    }
    return z3::mk_and(lits);
}

SatSolverResult::SatSolverResult(std::map<z3::expr, SatResult, Z3ExprComp> values) : _is_sat(true), _values(std::move(values)) {}


const std::map<std::string, SatSolverFactory> ISatSolver::s_solvers =
        {
                {"z3", [](z3::context& ctx) { return std::make_unique<Z3SatSolver>(ctx); }}
        };

