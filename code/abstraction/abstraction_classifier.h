#pragma once

//
// Created by galls2 on 14/10/19.
//


#include <structures/kripke_structure.h>
#include "abstract_state.h"

class AbstractClassificationTree;

class AbstractionClassifier {
public:
    explicit AbstractionClassifier(const KripkeStructure& kripke);

    const KripkeStructure& get_kripke() const;
private:
    const KripkeStructure& _kripke;
    std::map<std::set<std::string>, AbstractClassificationTree> _classification_trees;

};

class AbstractClassificationTree
{
public:
    AbstractClassificationTree(const AbstractionClassifier& classifier, const AbstractState& abs_state, const AbstractClassificationTree* parent=nullptr);
    size_t get_depth() const;
    bool is_leaf() const;

#ifndef DEBUG
    void set_split_string(const std::string& str);
#endif
private:
    const AbstractionClassifier& _classifier;
    const std::experimental::optional<std::function<bool(const ConcreteState&)>> _query;
    const std::map<bool, std::unique_ptr<AbstractClassificationTree>> _successors;
    const AbstractState& _abs_state;
    const AbstractClassificationTree* _parent;
    const size_t _depth;
#ifndef DEBUG
    std::string _split_string;
#endif
};
