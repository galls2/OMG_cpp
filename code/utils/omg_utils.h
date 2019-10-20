#pragma once

#include <array>
//
// Created by galls2 on 20/10/19.
//

template< typename T, typename ...Ts>
constexpr std::array<T, 1 + sizeof...(Ts)> make_array(T arg, Ts... args)
{
    return std::array<T, 1 + sizeof...(Ts)>({arg, args...});
}

