//
// Created by galls2 on 14/10/19.
//

#include "abstraction_classifier.h"

AbstractionClassifier::AbstractionClassifier(const KripkeStructure &kripke) : _kripke(kripke) {}

const KripkeStructure &AbstractionClassifier::get_kripke() const {
    return _kripke;
}

#ifndef DEBUG
void AbstractClassificationTree::set_split_string(const std::string& str) {
    _split_string = str;
}

AbstractClassificationTree::AbstractClassificationTree(const AbstractionClassifier &classifier,
        const AbstractState &abs_state, const AbstractClassificationTree *parent)
        : _classifier(classifier), _abs_state(abs_state), _parent(parent),
        _depth(_parent == nullptr ? 0 : _parent->get_depth() + 1)
{ }

size_t AbstractClassificationTree::get_depth() const {
    return _depth;
}

bool AbstractClassificationTree::is_leaf() const {
    return _successors.empty();
}

#endif
