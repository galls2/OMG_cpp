//
// Created by galls2 on 08/10/19.
//

#include <unordered_set>
#include "z3_utils.h"
#include "version_manager.h"
#include <model_checking/omg_model_checker.h>

z3::expr to_var(z3::context& ctx, size_t val) {
    return ctx.bool_const(VersionManager::new_version(val).data());
}

template <typename T>
z3::expr_vector iterable_to_expr_vec(z3::context& ctx, const T& iterable)
{
    z3::expr_vector expr_vector(ctx);
    for (const auto& it : iterable) expr_vector.push_back(it);
    return expr_vector;
}

z3::expr_vector vec_to_expr_vec(z3::context& ctx, const std::vector<z3::expr>& vec)
{
    return iterable_to_expr_vec<std::vector<z3::expr>>(ctx, vec);
}


template <typename T>
std::set<T> vector_to_set_debug(std::vector<T> vec)
{
    return std::set<T>(vec.begin(), vec.end());
}

std::set<z3::expr, Z3ExprComp> expr_vector_to_set(const z3::expr_vector& expr_vec)
{
    std::set<z3::expr, Z3ExprComp> s;
    for (size_t i = 0;i<expr_vec.size(); ++i) s.insert(expr_vec[i]);
    return s;
}

std::vector<z3::expr> expr_vector_to_vector(const z3::expr_vector& expr_vec)
{
    std::vector<z3::expr> s;
    for (size_t i = 0;i<expr_vec.size(); ++i) s.push_back(expr_vec[i]);
    return s;
}

SatResult Z3_val_to_sat_result(Z3_lbool v) {
    switch (v) {
        case Z3_lbool::Z3_L_UNDEF:
            return SatResult::UNDEF;
        case Z3_lbool::Z3_L_FALSE:
            return SatResult::FALSE;
        case Z3_lbool::Z3_L_TRUE:
            return SatResult::TRUE;
        default:
            throw(SatSolverResultException("Illegal Sat value"));
    }
}

std::string expr_vector_to_string(const z3::expr_vector &vec) {
    std::string res;
    for (size_t i = 0; i< vec.size(); ++i)
        res += vec[i].to_string()  + std::string(" ");
    return res;
}

std::string z3_expr_to_string(const std::vector<z3::expr> &vec) {
    std::string res;
    for (const auto &i : vec)
        res += i.to_string()  + std::string(" ");
    return res;
}



EEClosureResult
FormulaInductiveUtils::is_EE_inductive(AbstractState &to_close, const std::set<AbstractState *> &close_with, const std::string& sat_solver_str) {
    const KripkeStructure& kripke = to_close.get_kripke();
    const PropFormula& tr = kripke.get_tr();

    const z3::expr_vector ps_tr = tr.get_vars_by_tag("ps"), ns_tr = tr.get_vars_by_tag("ns"),
        in_0 = tr.get_vars_by_tag("in0"), in_1 = tr.get_vars_by_tag("in1");

    PropFormula src_formula = to_close.get_formula();
    z3::expr src_part = src_formula.get_raw_formula().substitute(src_formula.get_vars_by_tag("ps"), ps_tr)
                             .substitute(src_formula.get_vars_by_tag("in0"), in_0);

    z3::expr_vector dsts(ps_tr.ctx());
    for (const auto & closer : close_with)
    {
        PropFormula dst = closer->get_formula();
        z3::expr dst_raw_formula =
                FormulaUtils::negate(dst.get_raw_formula()
                                 .substitute(dst.get_vars_by_tag("ps"), ns_tr)
                                 .substitute(dst.get_vars_by_tag("in0"), in_1));
        dsts.push_back(dst_raw_formula);
    }

    z3::expr dst_part = z3::mk_and(dsts);

    z3::expr inductive_raw_formula = src_part && tr.get_raw_formula() && dst_part;
    PropFormula inductive_formula(inductive_raw_formula, {{"ps", ps_tr}, {"ns", ns_tr}});
    std::unique_ptr<ISatSolver> solver = ISatSolver::s_sat_solvers.at(sat_solver_str)(ps_tr.ctx());
    SatSolverResult res = solver->solve_sat(inductive_formula);
    if (res.get_is_sat())
    {
        return {true, std::experimental::optional<ConcreteState>(), std::experimental::optional<ConcreteState>()};
    }
    else
    {
        auto cstate_src = ConcreteState(kripke, FormulaUtils::get_conj_from_sat_result(ps_tr.ctx(), ps_tr, res));
        auto nstate_src = ConcreteState(kripke, FormulaUtils::get_conj_from_sat_result(ps_tr.ctx(), ps_tr, res));
        return {false, cstate_src, nstate_src};
    }
}

ConcretizationResult
FormulaInductiveUtils::concrete_transition_to_abs(const std::unordered_set<UnwindingTree *> &src_nodes,
                                                  const AbstractState &astate, const std::string &sat_solver_str) {
    const KripkeStructure &kripke = astate.get_kripke();
    const PropFormula &tr = kripke.get_tr();

    const z3::expr_vector ps_tr = tr.get_vars_by_tag("ps"), ns_tr = tr.get_vars_by_tag("ns"),
            in_0 = tr.get_vars_by_tag("in0"), in_1 = tr.get_vars_by_tag("in1");

    PropFormula astate_formula = astate.get_formula();
    const z3::expr dst_part = astate_formula.get_raw_formula()
            .substitute(astate_formula.get_vars_by_tag("ps"), ns_tr)
            .substitute(astate_formula.get_vars_by_tag("in0"), in_1);

    z3::context &ctx = dst_part.ctx();
    z3::expr_vector src_parts(ctx);

    size_t count_flags = 0;
    std::vector<z3::expr> flags;
    for (const UnwindingTree *src_node : src_nodes) {
        const z3::expr &src_formula = src_node->get_concrete_state().get_conjunct();
        z3::expr flag = ctx.bool_const(std::to_string(count_flags++).data());
        z3::expr flagged_src = (!flag) || src_formula;
        flags.push_back(flag);
        src_parts.push_back(flagged_src);
    }
    z3::expr src = z3::mk_or(src_parts);

    z3::expr raw_formula = src && tr.get_raw_formula() && dst_part;

    PropFormula is_tr_formula = PropFormula(raw_formula, {{"ps", ps_tr},
                                                          {"ns", ns_tr}});

    std::unique_ptr<ISatSolver> solver = ISatSolver::s_sat_solvers.at(sat_solver_str)(ctx);

    std::pair<int, SatSolverResult> res = solver->inc_solve_sat(is_tr_formula, flags);
    if (res.first < 0) {
        return ConcretizationResult(nullptr);
    } else {
        auto first_node_it = src_nodes.begin();
        std::advance(first_node_it, static_cast<size_t>(res.first));
        return ConcretizationResult(*first_node_it , ConcreteState(kripke, FormulaUtils::get_conj_from_sat_result(ps_tr.ctx(), ps_tr, res.second)));
    }
}

z3::expr FormulaUtils::negate(const z3::expr &expr) {
    return expr.is_not() ? expr.arg(0) : !expr;
}

z3::expr FormulaUtils::get_conj_from_sat_result(z3::context &ctx, const z3::expr_vector &conj_vars,
                                                const SatSolverResult &sat_result) {
    z3::expr_vector lits(ctx);
    for (size_t i = 0; i < conj_vars.size(); ++i) {
        z3::expr var = conj_vars[i];
        lits.push_back(sat_result.get_value(var) == SatResult::TRUE ? var : !var);
    }
    z3::expr conj = mk_and(lits);
    return conj;
}

