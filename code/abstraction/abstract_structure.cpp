//
// Created by galls2 on 04/10/19.
//

#include "abstract_structure.h"

AbstractStructure::AbstractStructure(const KripkeStructure &kripke) : _kripke(kripke)
{}

AbstractState &AbstractStructure::create_abs_state(const ConcreteState &cstate) {
    std::set<std::string> ap_strings = cstate.string_sat_aps();

    std::unique_ptr<CtlFormula::PropertySet> pos = std::make_unique<CtlFormula::PropertySet>();
    std::unique_ptr<CtlFormula::PropertySet> neg = std::make_unique<CtlFormula::PropertySet>();
    cstate.aps_by_sat(*pos, *neg);


    auto res =_abs_states.emplace(_kripke, std::move(pos), _kripke.get_aps(), cstate.get_bis0_formula());
    assert(res.second);

    return const_cast<AbstractState&>(*res.first);
}
