//
// Created by galls2 on 04/10/19.
//

#include "abstract_structure.h"

AbstractStructure::AbstractStructure(const KripkeStructure &kripke) : _kripke(kripke)
{}

AbstractState &AbstractStructure::create_abs_state(const ConcreteState &cstate) {
    CtlFormula::PropertySet pos, neg;
    cstate.aps_by_sat(pos, neg);

    auto res =_abs_states.emplace(_kripke, pos, _kripke.get_aps(), cstate.get_bis0_formula());
    assert(res.second);

    return const_cast<AbstractState&>(*res.first);
}

EEClosureResult AbstractStructure::is_EE_closure(AbstractState &to_close,
                                                 const std::set<std::reference_wrapper<AbstractState>> &close_with)
{
    std::set<const AbstractState*> p_closers, p_non_closers;
    if (_NE_may.find(&to_close) != _NE_may.end()) {
        p_non_closers = _NE_may[&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&to_close]
    }
    for (const std::reference_wrapper<AbstractState>& cl : close_with) {

    }
}
