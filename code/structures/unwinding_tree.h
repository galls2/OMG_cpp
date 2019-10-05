//
// Created by galls2 on 04/10/19.
//

#ifndef OMG_CPP_UNWINDING_TREE_H
#define OMG_CPP_UNWINDING_TREE_H

#include <memory>
#include <vector>
#include "kripke_structure.h"
#include "concrete_state.h"

class UnwindingTree {
public:
    UnwindingTree(const KripkeStructure& kripke, const ConcreteState& concrete_state, std::unique_ptr<UnwindingTree> parent) :
    _kripke(kripke), _concrete_label(concrete_state), _parent(std::move(parent))
    {
        _depth = (_parent) ? _parent->get_depth() + 1 : 0;
    }
    size_t get_depth() const { return  _depth; }

    const std::vector<std::unique_ptr<UnwindingTree>>& unwind_further();

private:
    const KripkeStructure& _kripke;
    const ConcreteState& _concrete_label;
    const std::unique_ptr<UnwindingTree> _parent;
    size_t _depth;
    std::vector<std::unique_ptr<UnwindingTree>> _successors;
};


#endif //OMG_CPP_UNWINDING_TREE_H
