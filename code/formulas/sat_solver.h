#pragma once
//
// Created by galls2 on 05/10/19.
//

#include <boost/variant.hpp>
#include "prop_formula.h"
#include <utils/omg_exception.h>


DECLARE_OMG_EXCEPTION(SatSolverResultException)

enum class SatResult {
    FALSE, UNDEF, TRUE
};


struct SatSolverResult
{
public:
    SatSolverResult();
    SatSolverResult(const z3::model& model, const std::vector<z3::expr>& vars);
    explicit SatSolverResult(const std::map<z3::expr, Z3_lbool >& values);
    explicit SatSolverResult(std::map<z3::expr, SatResult > values);

    SatResult get_value(const z3::expr& var) const;
    bool get_is_sat() const { return _is_sat; }
    z3::expr to_conjunt(z3::context& ctx) const;
private:
    bool _is_sat;
    std::map<z3::expr, SatResult> _values;

};

class ISatSolver
{
public:
    virtual SatSolverResult solve_sat(const PropFormula& formula) = 0;
    virtual std::vector<SatSolverResult> all_sat(const PropFormula& formula, const std::vector<z3::expr> &vars, bool complete_assignments=false) = 0;
};

class Z3SatSolver : public ISatSolver
{
public:
    explicit Z3SatSolver(z3::context& context) : _solver(context) {}
    SatSolverResult solve_sat(const PropFormula& formula) override;

    std::vector<SatSolverResult> all_sat(const PropFormula& formula, const std::vector<z3::expr> &vars, bool complete_assignments) override;

private:
    z3::solver _solver;

    z3::expr get_blocking_clause(const z3::model& model, const std::vector<z3::expr> &vector);

    void add_assignments(std::vector<SatSolverResult> &assignments, SatSolverResult result, const std::vector<z3::expr> &vars, bool complete_assignments);

};
