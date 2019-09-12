#pragma once

#include <sstream>

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems)
{
    std::stringstream ss(s);
    std::string item;
    while(std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}


template <typename T, size_t N>
std::array<T, N> split_to(const std::string& s, char delim, const std::function<size_t(std::string)>& converter)
{
    std::vector<std::string> items;
    split(s, delim, items);
    std::array<T, N> arr_to_ret;
    assert(items.size() == N);
    for (size_t i = 0; i < N; ++i) { arr_to_ret[i] = converter(items[i]); }
    return arr_to_ret;
}
