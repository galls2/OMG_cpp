//
// Created by galls2 on 05/10/19.
//

#include <z3.h>
#include "sat_solver.h"

SatSolverResult Z3SatSolver::solve_sat(const PropFormula &formula) {
    const z3::expr& raw_formula = formula.get_formula();
    _solver.add(raw_formula);
    if (_solver.check()) return SatSolverResult();
    return SatSolverResult(_solver.get_model(), formula.get_all_variables());
}

std::vector<SatSolverResult> Z3SatSolver::all_sat(const PropFormula &formula, const std::vector<z3::expr>& vars, bool complete_assignments = false ) {
    std::vector<SatSolverResult> assignments;
    const z3::expr &raw_formula = formula.get_formula();
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
     COMPLETE ME!!
    }
}

SatSolverResult::SatSolverResult() : _is_sat(false) { }

SatSolverResult::SatSolverResult(const z3::model& model, const std::vector<z3::expr>& vars) : _is_sat(true)
{
    auto& context = model.ctx();
    for (const auto& var : vars)
    {
        _values[var] = model.eval(var).bool_value();
    }
}

SatResult SatSolverResult::get_value(const z3::expr& var ) const {
    if (!_is_sat) throw SatSolverResultException("Formula is unsat");
    if (_values.find(var) != _values.end())
        switch (_values.at(var)) {
            case Z3_lbool::Z3_L_UNDEF:
                return SatResult::UNDEF;
            case Z3_lbool::Z3_L_FALSE:
                return SatResult::FALSE;
            case Z3_lbool::Z3_L_TRUE:
                return SatResult::TRUE;
            default:
                throw(SatSolverResultException("Illegal Sat value"));
        }
    else throw SatSolverResultException("Variables not in assignment");


}
