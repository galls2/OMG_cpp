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

const ConcreteState &UnwindingTree::get_concrete_state() const {
    return _concrete_label;
}

size_t UnwindingTree::get_depth() const {
    return _depth;
}

UnwindingTree::UnwindingTree(const KripkeStructure &kripke, const ConcreteState &concrete_state,
                             std::unique_ptr<UnwindingTree> parent): _kripke(kripke),
                             _concrete_label(concrete_state), _parent(std::move(parent))
{
    _depth = (_parent) ? _parent->get_depth() + 1 : 0;
}
