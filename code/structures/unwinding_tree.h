#pragma once
//
// Created by galls2 on 04/10/19.
//

#include <queue>
#include <memory>
#include <vector>
#include <experimental/optional>
#include <set>

#include "concrete_state.h"

class KripkeStructure;
class Goal;
class AbstractState;

class UnwindingTree {
public:
    UnwindingTree(const KripkeStructure& kripke, ConcreteState concrete_state, UnwindingTree * parent);
    size_t get_depth() const;
    const ConcreteState& get_concrete_state() const;
    const std::vector<std::unique_ptr<UnwindingTree>>& unwind_further();
    void reset_developed_in_tree();
    void set_developed(const Goal& goal);
    bool is_developed(const Goal& goal) const;
    void set_urgent(bool to_set);
    std::experimental::optional<std::reference_wrapper<AbstractState>>  get_abs() const;
    void set_abs(AbstractState& astate);
    bool is_urgent() const;
    const std::vector<std::unique_ptr<UnwindingTree>>& get_successors() const;
    bool exist_successors() const;
    void map_subtree(const std::function<void(UnwindingTree &)> &mapper,
                     const std::function<bool(const UnwindingTree &)> &activation_condition);
    void map_upwards(const std::function<void(UnwindingTree &)> &mapper,
                     const std::function<bool(const UnwindingTree &)> &last_node_pred);

    void add_label(bool positivity, const CtlFormula& spec);

    UnwindingTree* get_parent() const;

private:
    const KripkeStructure& _kripke;
    ConcreteState _cstate;
    std::experimental::optional<std::reference_wrapper<AbstractState>> _astate;
    UnwindingTree * const _parent;
    size_t _depth;
    bool _URGENT;
    std::vector<std::unique_ptr<UnwindingTree>> _successors;
    std::set<const Goal*> _developed;
};

auto cmp_nodes = [](const std::reference_wrapper<UnwindingTree>& a, const std::reference_wrapper<UnwindingTree>& b)
{
    if (a.get().is_urgent()) return true;
    if (b.get().is_urgent()) return false;
    return a.get().get_depth() < b.get().get_depth();
};

typedef std::priority_queue <std::reference_wrapper<UnwindingTree>,
        std::vector<std::reference_wrapper<UnwindingTree>>, decltype(cmp_nodes)> NodePriorityQueue;
