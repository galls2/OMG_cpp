//
// Created by galls2 on 04/10/19.
//

#ifndef OMG_CPP_UNWINDING_TREE_H
#define OMG_CPP_UNWINDING_TREE_H

#include <memory>
#include <vector>
#include <model_checking/omg_model_checker.h>
#include "kripke_structure.h"
#include "concrete_state.h"

class Goal;

class UnwindingTree {
public:
    UnwindingTree(const KripkeStructure& kripke, const ConcreteState& concrete_state, std::unique_ptr<UnwindingTree> parent);
    size_t get_depth() const;
    const ConcreteState& get_concrete_state() const;
    const std::vector<std::unique_ptr<UnwindingTree>>& unwind_further();
    void reset_developed_in_tree();

private:
    const KripkeStructure& _kripke;
    const ConcreteState& _concrete_label;
    const std::unique_ptr<UnwindingTree> _parent;
    size_t _depth;
    std::vector<std::unique_ptr<UnwindingTree>> _successors;
    std::map<Goal, bool> _developed;
};


#endif //OMG_CPP_UNWINDING_TREE_H
