//
// Created by galls2 on 04/10/19.
//

#include <utility>
#include <utils/omg_utils.h>
#include "unwinding_tree.h"
#include <abstraction/abstract_state.h>
const std::vector<std::unique_ptr<UnwindingTree>> &UnwindingTree::unwind_further() {
    if (!_successors.empty()) // Works as the Kripke structure is total
    {
        return _successors;
    }

    std::vector<ConcreteState> csuccessors = _cstate.get_successors();
    for (ConcreteState& cstate : csuccessors)
    {
        _successors.emplace_back(std::make_unique<UnwindingTree>(_kripke, std::move(cstate), this));
    }

    return _successors;
}

void UnwindingTree::reset_developed_in_tree()
{
    map_subtree([](UnwindingTree &node) { node._developed.clear(); }, [](const UnwindingTree &) { return true; });
}

const ConcreteState &UnwindingTree::get_concrete_state() const {
    return _cstate;
}

size_t UnwindingTree::get_depth() const {
    return _depth;
}

UnwindingTree::UnwindingTree(const KripkeStructure &kripke, ConcreteState concrete_state,
                             UnwindingTree * parent): _kripke(kripke),
                             _cstate(std::move(concrete_state)), _parent(parent), _URGENT(false)
{
    _depth = (_parent) ? _parent->get_depth() + 1 : 0;
}

void UnwindingTree::set_urgent(bool to_set) {
    _URGENT = to_set;
}

bool UnwindingTree::is_urgent() const {
    return _URGENT;
}

void UnwindingTree::set_developed(const Goal &goal)
{
    _developed.emplace(&goal);
}

void UnwindingTree::set_abs(AbstractState& astate)
{
    _astate.emplace(std::ref(astate));
}

std::experimental::optional<AStateRef> UnwindingTree::get_abs() const
{
    return _astate;
}

bool UnwindingTree::is_developed(const Goal &goal) const {
    bool exists = _developed.find(&goal) != _developed.end();
   // std::cout << "exists: " << exists << &goal << " " << *_developed.begin() << std::endl;
    return exists;
//    assert
}

void UnwindingTree::map_subtree(const std::function<void(UnwindingTree &)> &mapper,
                                const std::function<bool(const UnwindingTree &)> &activation_condition)
                        {
    if (activation_condition(*this)) {
        mapper(*this);
        for (const std::unique_ptr<UnwindingTree> &successor : _successors)
            successor->map_subtree(mapper, activation_condition);
    }
}

bool UnwindingTree::exist_successors() const {
    return !_successors.empty();
}

const std::vector<std::unique_ptr<UnwindingTree>> &UnwindingTree::get_successors() const {
    return _successors;
}

void UnwindingTree::map_upwards(const std::function<void(UnwindingTree &)> &mapper,
                                const std::function<bool(const UnwindingTree &)> &last_node_pred) {
    mapper(*this);
    if (!last_node_pred(*this))
    {
#ifdef DEBUG
      assert(_parent != nullptr);
#endif
      _parent->map_upwards(mapper, last_node_pred);
    }
}

void UnwindingTree::add_label(bool positivity, const CtlFormula &spec) {
#ifdef DEBUG
    assert(_astate);
#endif
    _astate->get().add_label(positivity, spec);
}

UnwindingTree *UnwindingTree::get_parent() const {
    return _parent;
}

bool UnwindingTree::any_of_upwards(const std::function<bool(const UnwindingTree &)> &predicate,
                                   const std::function<bool(const UnwindingTree &)> &last_node_pred) const {
    if (predicate(*this)) return true;
    if (!last_node_pred(*this))
    {
#ifdef DEBUG
        assert(_parent != nullptr);
#endif
        return _parent->any_of_upwards(predicate, last_node_pred);
    }
    return false;
}

bool UnwindingTree::is_concrete_lasso(const UnwindingTree &last_node) const {
    return any_of_upwards(
            [this](const UnwindingTree& n) {return this->get_concrete_state() == n.get_concrete_state();},
            [&last_node] (const UnwindingTree& n) { return &last_node == &n; }
            );
}
