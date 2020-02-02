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
    std::array<std::string, N> arr_to_ret;
    size_t elements_inserted = 0;

    std::stringstream ss(s);
    std::string item;

    while(std::getline(ss, item, delim) && elements_inserted < N) {
        arr_to_ret[elements_inserted++] = item;
    }
    assert(elements_inserted == N);
    return arr_to_ret;
}
