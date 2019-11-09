//
// Created by galls2 on 04/10/19.
//
#include <algorithm>
#include "abstract_structure.h"
#include <utils/z3_utils.h>
#include <model_checking/omg_model_checker.h>

AbstractStructure::AbstractStructure(const KripkeStructure &kripke, const OmgModelChecker* omg) : _kripke(kripke), _omg(omg)
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
    std::set<AbstractState*> p_closers, p_non_closers;
    if (_NE_may.find(&to_close) != _NE_may.end()) {
        p_non_closers = _NE_may[&to_close];
    }
    for (const std::reference_wrapper<AbstractState>& cl : close_with) {
        if (p_non_closers.find(&cl.get()) == p_non_closers.end()) p_closers.insert(&cl.get());
    }

    if (_E_may_over.find(&to_close) != _E_may_over.end())
    {
        const auto &possible_closers = _E_may_over[&to_close];
        for (const auto& closer_set : possible_closers)
        {
            bool is_subset = std::includes(p_closers.begin(), p_closers.end(), closer_set.begin(), closer_set.end());
            if (is_subset)
                return {true, std::experimental::optional<ConcreteState>(), std::experimental::optional<ConcreteState>()};
        }
    }

    if (_NE_may_over.find(&to_close) != _NE_may_over.end())
    {
        const auto &known_violations = _NE_may_over[&to_close];
        for (const auto &violation : known_violations)
        {
            bool is_subset = std::includes(violation.first.begin(), violation.first.end(), p_closers.begin(), p_closers.end());
            if (is_subset)
                return violation.second;
        }
    }

    EEClosureResult closure_result = FormulaInductiveUtils::is_EE_inductive(to_close, p_closers, get_omg()->_sat_solver);

    if (closure_result.is_closed)
    {
        if (_E_may_over.find(&to_close) == _E_may_over.end()) _E_may_over[&to_close] = {p_closers};
        else _E_may_over[&to_close].emplace_back(p_closers);
    } else
    {
        if (_NE_may_over.find(&to_close) == _NE_may_over.end())
        {
            AbstractState* src = &to_close;
            std::pair<std::set<AbstractState*>, EEClosureResult> new_entry = std::make_pair(std::move(p_closers), std::move(closure_result));
            std::vector<std::pair<std::set<AbstractState*>, EEClosureResult>> new_entry_vec = {new_entry};
            _NE_may_over.emplace(src, new_entry_vec);
        }
        else _NE_may_over[&to_close].emplace_back(p_closers, closure_result);
    }

    return closure_result;
}

const OmgModelChecker *AbstractStructure::get_omg() const{
    return _omg;
}
