//
// Created by galls2 on 21/03/20.
//

#ifndef OMG_CPP_GOAL_H
#define OMG_CPP_GOAL_H

#include <string>
#include <map>

class UnwindingTree;
class CtlFormula;

struct Goal
{
    Goal(UnwindingTree& node, const CtlFormula& spec, std::map<std::string, bool> properties);
    UnwindingTree &get_node();
    const CtlFormula &get_spec() const;
    const std::map<std::string, bool> &get_properties() const;
private:
    UnwindingTree& _node;
    const CtlFormula& _spec;
    const std::map<std::string, bool> _properties;
};


#endif //OMG_CPP_GOAL_H
