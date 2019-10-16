//
// Created by galls2 on 04/10/19.
//

#include "unwinding_tree.h"

const std::vector<std::unique_ptr<UnwindingTree>> &UnwindingTree::unwind_further() {
    if (!_successors.empty()) // Works as the Kripke structure is total
    {
        return _successors;
    }



    // Computing the successors

}

void UnwindingTree::reset_developed_in_tree()
{
    _developed.clear();
    for (const auto &it : _successors) it->reset_developed_in_tree();
}
