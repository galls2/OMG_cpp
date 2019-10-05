//
// Created by galls2 on 05/10/19.
//

#include "sat_solver.h"

SatSolverResult Z3SatSolver::solve_sat(const PropFormula &formula) {
    const z3::expr& raw_formula = formula.get_formula();
    _solver.add(raw_formula);
    if (_solver.check()) return SatSolverResult();
    return SatSolverResult(_solver.get_model(), formula.get_all_variables());
}

std::vector<SatSolverResult> Z3SatSolver::all_sat(const PropFormula &formula, const std::vector<z3::expr>& vars ) {
    std::vector<SatSolverResult> assignments;
    const z3::expr &raw_formula = formula.get_formula();
    z3::solver solver(raw_formula.ctx());

    solver.add(raw_formula);
    while (solver.check() == z3::sat)
    {
        z3::model m = solver.get_model();
        SatSolverResult res(m, vars);
        assignments.push_back(res);
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

SatSolverResult::SatSolverResult() : _is_sat(false) { }

SatSolverResult::SatSolverResult(const z3::model& model, const std::vector<z3::expr>& vars) : _is_sat(true)
{
    auto& context = model.ctx();
    for (const auto& var : vars)
    {
        _values[var] = z3::eq(model.eval(var), context.bool_val(true));
    }
}

bool SatSolverResult::get_value(const z3::expr& var ) const {
    if (!_is_sat) throw SatSolverResultException("Formula is unsat");
    return _values.at(var);
}
