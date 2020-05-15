#pragma once

#include <z3++.h>
#include <vector>
#include <set>
#include <formulas/sat_solver.h>
#include <abstraction/abstract_structure.h>
#include "omg_utils.h"

class AbstractState;
class UnwindingTree;
class ConcretizationResult;

class FormulaUtils
{
public:
    static z3::expr negate(const z3::expr& expr);

    static z3::expr get_conj_from_sat_result(z3::context &ctx, const z3::expr_vector &conj_vars,
                                                     const SatSolverResult &sat_result);

    static std::vector<z3::expr> get_vars_in_formula(z3::expr const & e);

    static bool is_cstate_conjunct(const z3::expr& f);

    static bool is_lit_agrees_with_conj(const z3::expr& conj, const z3::expr& var);

};

z3::expr to_var(z3::context& ctx, size_t val);

template <typename T>
z3::expr_vector iterable_to_expr_vec(z3::context& ctx, const T& iterable);

z3::expr_vector vec_to_expr_vec(z3::context& ctx, const std::vector<z3::expr>& vec);

template <typename IterableType1, typename IterableType2>
bool is_contained_z3_containers(const IterableType1& iter1, const IterableType2& iter2)
{
    return std::all_of(iter1.begin(), iter1.end(), [&iter2] (const z3::expr& it1)
    {
        return std::any_of(iter2.begin(), iter2.end(), [it1] (const z3::expr& it2)
        {
            return z3::eq(it1, it2);
        });

    });
}

template <typename T>
std::set<T> vector_to_set_debug(std::vector<T> vec);


template <typename VectorType>
Z3ExprSet expr_vector_to_set(const VectorType& expr_vec)
{
    Z3ExprSet s;
    for (size_t i = 0;i<expr_vec.size(); ++i) s.insert(expr_vec[i]);
    return s;
}

std::vector<z3::expr> expr_vector_to_vector(const z3::expr_vector& expr_vec);

SatResult Z3_val_to_sat_result(Z3_lbool v);


struct EEClosureResult;
struct AEClosureResult;

class FormulaInductiveUtils
{
public:
    static EEClosureResult is_EE_inductive(AbstractState& to_close, const ConstAbsStateSet& close_with);
    static EEClosureResult is_EE_inductive_inc(const PropFormula& skeleton, AbstractState& to_close, ISatSolver& solver);

    static PropFormula create_EE_inductive_formula_skeleton(AbsStateSet abs_lead, const std::set<ConstAStateRef> &close_with);
    static AEClosureResult is_AE_inductive(AbstractState& to_close, const ConstAbsStateSet& close_with);

    static ConcretizationResult concrete_transition_to_abs(const std::unordered_set<UnwindingTree*>& src_nodes, const AbstractState& astate);
};

struct SplitFormulas
{
    PropFormula query;
    PropFormula generalized_formula;
    PropFormula remainder_formula;
};

class FormulaSplitUtils
{
public:
    static SplitFormulas ex_pos(const z3::expr& state_conj, const PropFormula& src_astate_f,
            const std::set<const PropFormula*>& dsts_astates_f, const KripkeStructure& kripke);
    static SplitFormulas ex_neg(const z3::expr& state_conj, const PropFormula& src_astate_f,
          const std::set<const PropFormula*>& dsts_astates_f, const KripkeStructure& kripke, bool is_negate_dsts);
private:
    static void add_flags_to_conj(const z3::expr &conj, z3::context &ctx, z3::expr_vector &assumptions,
                      z3::expr_vector &assertions,
                      std::map<z3::expr, unsigned int, Z3ExprComp> &assumptions_map,
                      const std::string &assumption_prefix);

    static z3::expr_vector get_assertions_from_unsat_core(const z3::expr &state_conj, z3::context &ctx,
                                                          std::map<z3::expr, unsigned int, Z3ExprComp> &assumptions_map,
                                                          const z3::expr_vector &unsat_core);

    static z3::expr merge_dst_astate_formulas(const std::set<const PropFormula *> &dsts_astates_f, const PropFormula& tr, z3::context& ctx);
    static void find_proving_inputs(const z3::expr& state_conj, const PropFormula& tr, z3::expr& dst, z3::expr_vector& input_values);

    static SplitFormulas
    get_split_formulas(const z3::expr &state_conj, const PropFormula &src_astate_formula, const PropFormula &tr,
                       z3::context &ctx, z3::expr_vector &assumptions,
                       std::map<z3::expr, unsigned int, Z3ExprComp> &assumptions_map, const z3::expr &final_assumption,
                       const PropFormula &formula_to_check);
};