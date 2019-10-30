//
// Created by galls2 on 04/10/19.
//

#ifndef OMG_CPP_ABSTRACT_STRUCTURE_H
#define OMG_CPP_ABSTRACT_STRUCTURE_H


#include <structures/kripke_structure.h>
#include "abstract_state.h"

struct EEClosureResult;

class AbstractStructure {
public:
    explicit AbstractStructure(const KripkeStructure& kripke);
    AbstractState& create_abs_state(const ConcreteState& cstate);
    EEClosureResult is_EE_closure(AbstractState& to_close , const std::set<std::reference_wrapper<AbstractState>>& close_with);
private:
    const KripkeStructure& _kripke;
    std::set<AbstractState> _abs_states;

    std::map<const AbstractState* const, std::set<const AbstractState* const>> _NE_may;
    std::map<const AbstractState* const, std::set<const AbstractState* const>> _E_must;

    //E MAY OVER, , NE MAY OVER
};


#endif //OMG_CPP_ABSTRACT_STRUCTURE_H
