//
// Created by galls2 on 04/10/19.
//

#include "unwinding_tree.h"

const std::vector<std::unique_ptr<UnwindingTree>> &UnwindingTree::unwind_further() {
    if (!_successors.empty()) // Works as the Kripke structure is total
    {
        return _successors;
    }

    const std::vector<ConcreteState> csuccessors = _cstate.get_successors();

    // Computing the successors

}

void UnwindingTree::reset_developed_in_tree()
{
    map([](UnwindingTree& node){node._developed.clear();}, [](const UnwindingTree&) {return true;});
//    _developed.clear();
//    for (const auto &it : _successors) it->reset_developed_in_tree();
}

const ConcreteState &UnwindingTree::get_concrete_state() const {
    return _cstate;
}

size_t UnwindingTree::get_depth() const {
    return _depth;
}

UnwindingTree::UnwindingTree(const KripkeStructure &kripke, ConcreteState &concrete_state,
                             std::unique_ptr<UnwindingTree> parent): _kripke(kripke),
                             _cstate(concrete_state), _parent(std::move(parent)), _URGENT(false)
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

std::experimental::optional<std::reference_wrapper<AbstractState>> UnwindingTree::get_abs() const
{
    return _astate;
}

bool UnwindingTree::is_developed(const Goal &goal) const {
    bool exists = _developed.find(&goal) == _developed.end();
    return exists;
}

void UnwindingTree::map(const std::function<void(UnwindingTree &)> &mapper,
                        const std::function<bool(const UnwindingTree &)> &activation_condition)
                        {
    if (activation_condition(*this)) {
        mapper(*this);
        for (const std::unique_ptr<UnwindingTree> &successor : _successors)
            successor->map(mapper, activation_condition);
    }
}
