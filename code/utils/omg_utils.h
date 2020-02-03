#pragma once
#include <map>
#include <functional>
#include <memory>
#include <array>
#include <formulas/sat_solver.h>
//
// Created by galls2 on 20/10/19.
//

template< typename T, typename ...Ts>
constexpr std::array<T, 1 + sizeof...(Ts)> make_array(T arg, Ts... args)
{
    return std::array<T, 1 + sizeof...(Ts)>({arg, args...});
}

template <typename T>
void print_vec(const std::vector<T>& vec)
{
    for (const auto& it : vec)
        std::cout << it << " ";
    std::cout << std::endl;
}