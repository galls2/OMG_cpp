
//
// Created by galls2 on 12/10/19.
//

#include <utility>
#include <algorithm>
#include <iterator>
#include "abstract_state.h"

#include <abstraction/abstraction_classifier.h>

AbstractState::AbstractState(const KripkeStructure &kripke, CtlFormula::PropertySet pos_labels,
                             CtlFormula::PropertySet atomic_labels, PropFormula sym_rep)
                             : _kripke(kripke), _pos_labels(std::move(pos_labels)),
                             _atomic_labels(std::move(atomic_labels)), _sym_rep(std::move(sym_rep))
{
    std::set_difference(_atomic_labels.begin(), _atomic_labels.end(), _pos_labels.begin(), _pos_labels.end(),
                        std::inserter(_neg_labels, _neg_labels.end()));
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

bool AbstractState::is_final_classification() const {
    return _cl_node->is_leaf();
}

AbstractClassificationNode *AbstractState::get_cl_node() const {
    return _cl_node;
}

const KripkeStructure &AbstractState::get_kripke() const {
    return _kripke;
}

bool operator<(const AbstractState &lhs, const AbstractState &rhs) {
    return lhs.get_cl_node() < rhs.get_cl_node();
}

PropFormula AbstractState::get_formula() const
{
    return _sym_rep;
}

void AbstractState::set_cl_node(AbstractClassificationNode *const cl_node) {
    _cl_node = cl_node;
}
