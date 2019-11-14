#pragma once

#include <z3++.h>
#include <vector>
#include <set>
#include <formulas/sat_solver.h>
#include <abstraction/abstract_structure.h>

class AbstractState;
class UnwindingTree;
class ConcretizationResult;

class FormulaUtils
{
public:
    static z3::expr negate(const z3::expr& expr);

    static z3::expr get_conj_from_sat_result(z3::context &ctx, const z3::expr_vector &conj_vars,
                                                     const SatSolverResult &sat_result);
};

z3::expr to_var(z3::context& ctx, size_t val);

template <typename T>
z3::expr_vector iterable_to_expr_vec(z3::context& ctx, const T& iterable);

z3::expr_vector vec_to_expr_vec(z3::context& ctx, const std::vector<z3::expr>& vec);


template <typename T>
std::set<T> vector_to_set_debug(std::vector<T> vec);

std::set<z3::expr, Z3ExprComp> expr_vector_to_set(const z3::expr_vector& expr_vec);

std::vector<z3::expr> expr_vector_to_vector(const z3::expr_vector& expr_vec);

SatResult Z3_val_to_sat_result(Z3_lbool v);

std::string expr_vector_to_string(const z3::expr_vector& vec);


std::string z3_expr_to_string(const std::vector<z3::expr>& vec);

class FormulaInductiveUtils
{
public:
    static EEClosureResult is_EE_inductive(AbstractState& to_close, const std::set<AbstractState*>& close_with, const std::string& sat_solver_str);
    static ConcretizationResult concrete_transition_to_abs(const std::unordered_set<const UnwindingTree*>& src_nodes, const AbstractState& astate, const std::string& sat_solver_str);
};