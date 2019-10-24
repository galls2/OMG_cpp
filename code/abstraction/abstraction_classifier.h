#pragma once

//
// Created by galls2 on 14/10/19.
//


#include <structures/kripke_structure.h>
#include "abstract_state.h"

class AbstractClassificationNode;

class AbstractionClassifier {
public:
    explicit AbstractionClassifier(const KripkeStructure& kripke);

    bool exists_classification(const ConcreteState& cstate) const;
    AbstractClassificationNode& add_classification_tree(const ConcreteState& cstate, AbstractState& astate);
    AbstractState& classify(const ConcreteState &cstate);
    const KripkeStructure& get_kripke() const;
    AbstractState& update_classification(const AbstractState& astate, const ConcreteState& cstate);
private:
    const KripkeStructure& _kripke;
    std::map<std::set<std::string>, std::unique_ptr<AbstractClassificationNode>> _classification_trees;

};

class AbstractClassificationNode
{
public:
    AbstractClassificationNode(AbstractionClassifier& classifier, AbstractState* abs_state, const AbstractClassificationNode* parent=nullptr);
    size_t get_depth() const;
    bool is_leaf() const;
    AbstractState& classify(const ConcreteState& cstate) const;

#ifndef DEBUG
    void set_split_string(const std::string& str);
#endif
private:
    const AbstractionClassifier& _classifier;
    const std::experimental::optional<std::function<bool(const ConcreteState&)>> _query;
    const std::map<bool, std::unique_ptr<AbstractClassificationNode>> _successors;
    AbstractState* _abs_state;
    const AbstractClassificationNode* _parent;
    const size_t _depth;
#ifndef DEBUG
    std::string _split_string;
#endif
};
