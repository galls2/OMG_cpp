//
// Created by galls2 on 04/10/19.
//

#include <utility>
#include <utils/omg_utils.h>
#include "unwinding_tree.h"
#include <abstraction/abstract_state.h>
#include <utils/Stats.h>

using namespace avy;

const std::vector<std::unique_ptr<UnwindingTree>> &UnwindingTree::unwind_further()
{
    throw 'f';

    /*
    AVY_MEASURE_FN;

    if (!_successors.empty()) // Works as the Kripke structure is total
    {
        return _successors;
    }

    auto& csuccessors = _cstate.get_successors();
    for (ConcreteState& cstate : csuccessors)
    {
        _successors.emplace_back(std::make_unique<UnwindingTree>(_kripke, cstate, this));
    }
    */
    return _successors;
}

void UnwindingTree::reset_developed_in_tree()
{
    map_subtree([](UnwindingTree &node) { node._developed.clear(); }, [](const UnwindingTree &) { return true; });
}

const ConcreteSet &UnwindingTree::get_concrete_set() const {
    return _cset;
}

size_t UnwindingTree::get_depth() const {
    return _depth;
}

UnwindingTree::UnwindingTree(const KripkeStructure &kripke, ConcreteSet concrete_set,
                             UnwindingTree * parent): _kripke(kripke),
                             _cset(std::move(concrete_set)), _parent(parent), _URGENT(false)
{
    AVY_MEASURE_FN;

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

void UnwindingTree::set_abs(AbsStateSet astate_set)
{
    _astates = std::move(astate_set);
}

const AbsStateSet& UnwindingTree::get_abs() const
{
    return _astates;
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
    assert(_astate->get().is_final_classification());
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
            [this](const UnwindingTree& n) {return get_concrete_set() == n.get_concrete_set();},
            [&last_node] (const UnwindingTree& n) { return &last_node == &n; }
            );
}

std::pair<CandidateSet, UnwindingTree*> UnwindingTree::find_abstract_lasso(const UnwindingTree &last_node) {
    CandidateSet to_return;

    assert(get_abs() && get_abs()->get().is_final_classification());
    AbstractState& abs_to_find = *get_abs();

    UnwindingTree* lasso_base = nullptr;
    bool is_lasso = false;

    auto mapper = [&abs_to_find, &is_lasso, &to_return, &lasso_base, this](UnwindingTree& n) {
        assert(n.get_abs() && n.get_abs()->get().is_final_classification());
        AbstractState &current_abs = *n.get_abs();
        if (current_abs == abs_to_find && this != &n) { is_lasso = true; lasso_base = &n; }
        to_return[&current_abs].emplace(&n);
    };

    auto stop_predicate = [&abs_to_find, &last_node] (const UnwindingTree& n) {
        assert(n.get_abs());
        AbstractState &current_abs = *n.get_abs();
        return current_abs == abs_to_find || &n == &last_node;
    };

    map_upwards(mapper, stop_predicate);

    if (!is_lasso) return {};
    else return {to_return, lasso_base};
}

#ifdef DEBUG
std::string UnwindingTree::to_string() const {
    return _cset.to_bitvec_str() + std::string(", depth: ")+std::to_string(_depth);
}
#endif


