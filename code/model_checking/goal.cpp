//
// Created by galls2 on 21/03/20.
//
#include "goal.h"
#include <structures/unwinding_tree.h>

UnwindingTree &Goal::get_node() {
        return _node;
}

const CtlFormula &Goal::get_spec() const {
        return _spec;
}

const std::map<std::string, bool> &Goal::get_properties() const {
        return _properties;
}

Goal::Goal(UnwindingTree &node, const CtlFormula &spec,
           std::map<std::string, bool> properties)
 : _node(node), _spec(spec), _properties(std::move(properties))
{}

#ifdef DEBUG
std::string Goal::to_string() const {
        return std::string("Checking goal: node ") + _node.to_string() + ". Spec: " + _spec.to_string();
}
#endif


