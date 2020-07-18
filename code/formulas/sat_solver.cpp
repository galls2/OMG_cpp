//
// Created by galls2 on 05/10/19.
//

#include <algorithm>
#include <set>
#include <utils/z3_utils.h>
#include "sat_solver.h"

SatSolverResult Z3SatSolver::solve_sat(const PropFormula &formula) {
    const z3::expr& raw_formula = formula.get_raw_formula().simplify(); // TODO .simplify();
    _solver.add(raw_formula);
    z3::check_result sat_res = _solver.check();
    if (sat_res == z3::unsat) return SatSolverResult();
    else if (sat_res == z3::sat) return SatSolverResult(_solver.get_model(), formula.get_all_variables());
    else { assert(sat_res == z3::unknown); throw SatSolverResultException("SAT result is unknown"); }
}

std::vector<SatSolverResult> Z3SatSolver::all_sat(const PropFormula &formula, const std::vector<z3::expr>& vars, bool complete_assignments = false ) {
    std::vector<SatSolverResult> assignments;
    const z3::expr &raw_formula = formula.get_raw_formula().simplify();
    z3::solver solver(raw_formula.ctx());

    solver.add(raw_formula);
    while (solver.check() == z3::sat)
    {
        z3::model m = solver.get_model();

        SatSolverResult res(m, vars);
//        const auto& assertions = solver.assertions();
//        res.generalize_assignment(assertions);

        add_assignments(assignments ,res, vars, complete_assignments);
        z3::expr blocking_clause = get_blocking_clause(res, vars);
        solver.add(blocking_clause);
    }
    return assignments;
}

z3::expr Z3SatSolver::get_blocking_clause(const SatSolverResult& res, const std::vector<z3::expr> &var_vector) {
    z3::context& ctx = var_vector.begin()->ctx();
    z3::expr_vector literals(ctx);
    for (const z3::expr& var : var_vector)
    {
        auto res_value = res.get_value(var);
        if (res_value != SatResult::UNDEF)
        {
            literals.push_back((res_value == SatResult::TRUE) ? (!var) : (var));
        }
    }
    return z3::mk_or(literals);
}

void Z3SatSolver::add_assignments(std::vector<SatSolverResult> &assignemnts, SatSolverResult result,
                                  const std::vector<z3::expr> &vars, bool complete_assignments) {
    assert(result.get_is_sat());
    if (!complete_assignments) {
        assignemnts.push_back(result);
        return;
    }
    else
    {
        std::set<size_t> undef_idxs;
        for (size_t i = 0; i < vars.size(); ++i) if (result.get_value(vars[i]) == SatResult::UNDEF) undef_idxs.insert(i);
        ssize_t iter_max = (1U << undef_idxs.size());
#ifdef DEBUG
        assert(iter_max >= 0);
#endif
        for (size_t i = 0; i < ((size_t)iter_max); ++i)
        {
            size_t undef_idx = 0;
            std::map<z3::expr, SatResult, Z3ExprComp> vals;
            for (size_t j = 0; j < vars.size(); ++j)
            {
                if (undef_idxs.find(j) == undef_idxs.end()) {
                    vals.emplace(vars[j], result.get_value(vars[j]));
                }
                else
                {
                    bool is_true_val = (i & (1U << undef_idx)) > 0;
                    undef_idx++;
                    vals.emplace(vars[j], is_true_val ? SatResult::TRUE : SatResult::FALSE);
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
    auto res = _values.find(var);
    if (res == _values.end())
    {
        throw SatSolverResultException("Variables not in assignment");
    }
    return res->second;
}

z3::expr SatSolverResult::to_conjunct(const Z3ExprSet& to_flip) const {
    z3::context& ctx = _values.begin()->first.ctx();
    z3::expr_vector lits(ctx);
    for (const auto & value : _values) {
        if (value.second != SatResult::UNDEF) {
            bool is_to_flip = to_flip.find(value.first) != to_flip.end();
            lits.push_back((value.second == (is_to_flip ? SatResult::FALSE : SatResult::TRUE))
                                    ? (value.first) : (!value.first));
        }
    }
    return z3::mk_and(lits);
}

SatSolverResult::SatSolverResult(std::map<z3::expr, SatResult, Z3ExprComp> values) : _is_sat(true), _values(std::move(values)) {}

void SatSolverResult::generalize_assignment(const z3::expr_vector& assertions) {
    z3::expr united_assertions = z3::mk_and(assertions);
    auto &ctx = assertions.ctx();

#ifdef DEBUG
    z3::solver assert_solver(ctx);
        assert_solver.add(united_assertions);
        assert_solver.add(to_conjunct());
        assert(assert_solver.check() == z3::sat);
#endif

    z3::solver solver(ctx);
   // solver.add(united_assertions);

    for (auto var_it = _values.begin(); var_it != _values.end(); ++var_it) {
        if (var_it->second == SatResult::UNDEF) continue;


        z3::expr flipped_conj = to_conjunct({var_it->first});
        z3::expr_vector orig(ctx), to_replace(ctx);
        for (uint i = 0; i < flipped_conj.num_args(); ++i)
        {
            auto lit = flipped_conj.arg(i);
            auto var = lit.is_not() ? lit.arg(0) : lit;
            orig.push_back(var);
            to_replace.push_back(ctx.bool_val(!lit.is_not()));
        }

        solver.push();
        z3::expr subtituted_assertion = united_assertions.substitute(orig, to_replace).simplify();
        solver.add(subtituted_assertion);
        auto sat_res = solver.check();
        if (sat_res == z3::sat)
        {
   //         std::cout << "GEN CONDUCTED" << std::endl;
            var_it->second = SatResult::UNDEF;
        }


        solver.pop();
    }
}

const std::map<std::string, SatSolverFactory> ISatSolver::s_solvers =
        {
                {"z3", [](z3::context& ctx) { return std::make_unique<Z3SatSolver>(ctx); }}
        };

