#pragma once
//
// Created by galls2 on 05/10/19.
//
#include <memory>
#include <set>
#include <boost/variant.hpp>
#include <utils/omg_exception.h>
#include <functional>
#include <map>
#include <z3++.h>

class PropFormula;

DECLARE_OMG_EXCEPTION(SatSolverResultException)

enum class SatResult {
    FALSE, UNDEF, TRUE
};


struct Z3ExprComp
{
    bool operator()(const z3::expr& a, const z3::expr& b) const
    {
        return a.to_string() < b.to_string();
    }

};

typedef std::set<z3::expr, Z3ExprComp> Z3ExprSet;

struct SatSolverResult
{
public:
    SatSolverResult();
    SatSolverResult(const z3::model& model, const std::vector<z3::expr>& vars);
    explicit SatSolverResult(const std::map<z3::expr, Z3_lbool >& values);
    explicit SatSolverResult(std::map<z3::expr, SatResult, Z3ExprComp > values);

    SatResult get_value(const z3::expr& var) const;
    bool get_is_sat() const { return _is_sat; }
    z3::expr to_conjunt(z3::context& ctx) const;
private:
    bool _is_sat;
    std::map<z3::expr, SatResult, Z3ExprComp> _values;

};

class ISatSolver;
typedef std::function<std::unique_ptr<ISatSolver>(z3::context&)> SatSolverFactory;

class ISatSolver
{
public:
    virtual SatSolverResult solve_sat(const PropFormula& formula) = 0;
    virtual bool is_sat(const z3::expr& formula) = 0;

    virtual std::pair<int, SatSolverResult> inc_solve_sat(const PropFormula& formula, const std::vector<z3::expr>& flags) = 0;
    virtual std::vector<SatSolverResult> all_sat(const PropFormula& formula, const std::vector<z3::expr> &vars, bool complete_assignments=false) = 0;
    virtual z3::expr_vector get_unsat_core(const PropFormula& formula, z3::expr_vector& assumptions) = 0;
    static const std::map<std::string, SatSolverFactory> s_solvers;
    virtual ~ISatSolver() = default;
};

class Z3SatSolver : public ISatSolver
{
public:
    explicit Z3SatSolver(z3::context& context) : _solver(context) {}
    SatSolverResult solve_sat(const PropFormula& formula) override;
    bool is_sat(const z3::expr& formula) override;

    std::vector<SatSolverResult> all_sat(const PropFormula& formula, const std::vector<z3::expr> &vars, bool complete_assignments) override;
    std::pair<int, SatSolverResult> inc_solve_sat(const PropFormula& formula, const std::vector<z3::expr>& flags) override;
    z3::expr_vector get_unsat_core(const PropFormula& formula, z3::expr_vector& assumptions) override;
    ~Z3SatSolver() override = default;

private:
    z3::solver _solver;

    static z3::expr get_blocking_clause(const SatSolverResult& model, const std::vector<z3::expr> &vector);

    void add_assignments(std::vector<SatSolverResult> &assignments, SatSolverResult result, const std::vector<z3::expr> &vars, bool complete_assignments);

};
