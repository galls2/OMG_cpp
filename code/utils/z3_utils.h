#pragma once

#include <z3++.h>
#include <vector>
#include <set>
#include <formulas/sat_solver.h>

z3::expr to_var(z3::context& ctx, size_t val);

template <typename T>
z3::expr_vector iterable_to_expr_vec(z3::context& ctx, const T& iterable);

z3::expr_vector vec_to_expr_vec(z3::context& ctx, const std::vector<z3::expr>& vec);


template <typename T>
std::set<T> vector_to_set_debug(std::vector<T> vec);

std::set<z3::expr> expr_vector_to_set(const z3::expr_vector& expr_vec);

std::vector<z3::expr> expr_vector_to_vector(const z3::expr_vector& expr_vec);

SatResult Z3_val_to_sat_result(Z3_lbool v);