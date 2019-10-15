//
// Created by galls2 on 14/10/19.
//

#include "abstraction_classifier.h"

AbstractionClassifier::AbstractionClassifier(const KripkeStructure &kripke) : _kripke(kripke) {}

const KripkeStructure &AbstractionClassifier::get_kripke() const {
    return _kripke;
}

bool AbstractionClassifier::exists_classification(const ConcreteState &cstate) const {
    std::set<std::string> ap_strings;

}

#ifndef DEBUG
void AbstractClassificationNode::set_split_string(const std::string& str) {
    _split_string = str;
}
#endif

AbstractClassificationNode::AbstractClassificationNode(const AbstractionClassifier &classifier,
        const AbstractState &abs_state, const AbstractClassificationNode *parent)
        : _classifier(classifier), _abs_state(abs_state), _parent(parent),
        _depth(_parent == nullptr ? 0 : _parent->get_depth() + 1)
{ }

size_t AbstractClassificationNode::get_depth() const {
    return _depth;
}

bool AbstractClassificationNode::is_leaf() const {
    return _successors.empty();
}

AbstractState &AbstractClassificationNode::classify(const ConcreteState &cstate) const {
    if (_successors.empty())
    {
        assert(_abs_state);
        return _abs_state.value();
    }
    else
    {
        assert(_query);
        const auto& query = _query.value();
        bool successor = query(cstate);
        AbstractState& classification_result = _successors.at(successor)->classify(cstate);
        return classification_result;
    }
}
