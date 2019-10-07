//
// Created by galls2 on 07/10/19.
//

#ifndef OMG_CPP_CARTESIAN_PRODUCT_GENERATOR_H
#define OMG_CPP_CARTESIAN_PRODUCT_GENERATOR_H

#include <vector>
#include <experimental/optional>
#include <cassert>

template <typename T>
class CartesianProductGenerator {
public:
    explicit CartesianProductGenerator(const std::vector<std::vector<T>>& src) : _src(src), _current(_src.size()) { }
    std::vector<T> get_initial()
    {
        std::vector<T> to_return;
        _current.clear();
        for (auto& vec : _src)
        {
            if (vec.empty()) return std::vector<T>();
            _current.push_back(0);
            to_return.push_back(vec[0]);
        }
        return to_return;
    }
    std::experimental::optional<std::vector<T>> get_next()
    {
        bool stop = false, found = false;
        size_t vec_idx = 0;
        while (!stop && !found)
        {
            if (_current[vec_idx] < _src[vec_idx].size())
            {
                found = true;
                ++_current[vec_idx];
            }
            else
            {
                if (vec_idx < _current.size())
                {
                    _current[vec_idx] = 0;
                    ++vec_idx;
                }
                else stop = true;
            }
        }
        if (stop) return std::experimental::optional<std::vector<T>>();
        else
        {
            assert(found);
            std::vector<T> to_return;
            for (size_t i = 0; i<_current.size(); ++i) to_return.push_back(_src[i][_current[i]]);
            return to_return;

        }
    }

private:

    const std::vector<std::vector<T>> _src;
    std::vector<size_t> _current;
};


#endif //OMG_CPP_CARTESIAN_PRODUCT_GENERATOR_H
