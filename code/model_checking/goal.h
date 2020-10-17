//
// Created by galls2 on 21/03/20.
//

#ifndef OMG_CPP_GOAL_H
#define OMG_CPP_GOAL_H

#include <string>
#include <map>
#include <structures/concrete_set.h>

class UnwindingTree;
class CtlFormula;

struct Goal
{
    Goal(UnwindingTree& node, const CtlFormula& spec, std::map<std::string, bool> properties);
    UnwindingTree &get_node();
    const CtlFormula &get_spec() const;
    const std::map<std::string, bool> &get_properties() const;

#ifdef DEBUG
    std::string to_string() const;
#endif
private:
    UnwindingTree& _node;
    const CtlFormula& _spec;
    const std::map<std::string, bool> _properties;
};

struct OmgMcResult
{
    const ConcreteSet sat_cset;
    const ConcreteSet unsat_cset;
};

#endif //OMG_CPP_GOAL_H
