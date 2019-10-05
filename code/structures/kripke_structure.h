//
// Created by galls2 on 29/09/19.
//

#ifndef OMG_CPP_KRIPKE_STRUCTURE_H
#define OMG_CPP_KRIPKE_STRUCTURE_H


#include <z3++.h>
#include <formulas/prop_formula.h>
#include <set>
#include "concrete_state.h"

class KripkeStructure {
public:
    KripkeStructure(PropFormula tr, std::set<std::string> aps) : _transitions(std::move(tr)), _aps(std::move(aps)) {}
    const PropFormula& get_tr() const { return _transitions; }
    std::vector<ConcreteState> get_successors(const ConcreteState& state);
private:
    const PropFormula _transitions;
    const std::set<std::string> _aps;

};


#endif //OMG_CPP_KRIPKE_STRUCTURE_H
