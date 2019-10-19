
//
// Created by galls2 on 12/10/19.
//

#include <utility>
#include <algorithm>
#include <iterator>
#include "abstract_state.h"

AbstractState::AbstractState(const KripkeStructure &kripke, std::set<const CtlFormula*> pos_labels,
                             std::set<const CtlFormula*> atomic_labels, PropFormula sym_rep)
                             : _kripke(kripke), _pos_labels(std::move(pos_labels)),
                             _atomic_labels(std::move(atomic_labels)), _sym_rep(std::move(sym_rep))
{
    std::set_difference(atomic_labels.begin(), atomic_labels.end(), pos_labels.begin(), pos_labels.end(),
                        std::inserter(_neg_labels, _neg_labels.end()));
}

bool AbstractState::operator<(const AbstractState &other) const {
    return _cl_node < other._cl_node;
}

bool AbstractState::is_neg_labeled(const CtlFormula &spec) const {
    return _neg_labels.find(&spec) != _neg_labels.end();
}

bool AbstractState::is_pos_labeled(const CtlFormula &spec) const {
    return _pos_labels.find(&spec) != _pos_labels.end();
}

void AbstractState::add_label(bool positivity, const CtlFormula &spec)
{
    if (positivity)
    {
        _pos_labels.insert(&spec);
    }
    else
    {
        _neg_labels.insert(&spec);
    }
}
