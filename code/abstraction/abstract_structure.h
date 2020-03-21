//
// Created by galls2 on 04/10/19.
//

#ifndef OMG_CPP_ABSTRACT_STRUCTURE_H
#define OMG_CPP_ABSTRACT_STRUCTURE_H


#include <structures/kripke_structure.h>
#include "abstract_state.h"

struct EEClosureResult
{
    bool is_closed = false;
    std::experimental::optional<ConcreteState> src;
    std::experimental::optional<ConcreteState> dst;
};

class OmgModelChecker;

class AbstractStructure {
public:
    explicit AbstractStructure(const KripkeStructure& kripke, const OmgModelChecker* omg);
    AbstractState& create_abs_state(const ConcreteState& cstate);
    EEClosureResult is_EE_closure(AbstractState& to_close , const std::set<std::reference_wrapper<AbstractState>>& close_with);
    const OmgModelChecker* get_omg() const;
    void split_abs_state_by_son(const ConcreteState& src_cstate, AbstractState& src_abs, const std::set<const bstractState*>&  dsts_abs);
private:
    const KripkeStructure& _kripke;
    const OmgModelChecker* _omg;
    std::set<AbstractState> _abs_states;

    std::map<AbstractState* const, std::set<AbstractState*>> _NE_may;
    std::map<const AbstractState* const, std::vector<std::set<const AbstractState* const>>> _E_must;
    std::map<AbstractState* const, std::vector<std::set<AbstractState*>>> _E_may_over;
    std::map<AbstractState* const, std::vector<std::pair<std::set<AbstractState*>, EEClosureResult>>> _NE_may_over;

    //E MAY OVER, , NE MAY OVER
};


#endif //OMG_CPP_ABSTRACT_STRUCTURE_H
