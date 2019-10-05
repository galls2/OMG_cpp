#pragma once

#include <z3++.h>
#include <formulas/prop_formula.h>
#include <set>
#include <structures/concrete_state.h>

class KripkeStructure {
public:
    KripkeStructure(PropFormula tr, std::set<std::string> aps) : _transitions(std::move(tr)), _aps(std::move(aps)) {}
    const PropFormula& get_tr() const { return _transitions; }
private:
    const PropFormula _transitions;
    const std::set<std::string> _aps;

};

