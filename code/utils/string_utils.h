#pragma once

#include <sstream>
#include <vector>
#include <array>
#include <cassert>
#include <string>

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);


template <size_t N>
std::array<std::string, N> split_to(const std::string& s, char delim)
{
    std::vector<std::string> items;
    split(s, delim, items);
    std::array<std::string, N> arr_to_ret;
    assert(items.size() == N);
    for (size_t i = 0; i < N; ++i) { arr_to_ret[i] = items[i]; }
    return arr_to_ret;
}

