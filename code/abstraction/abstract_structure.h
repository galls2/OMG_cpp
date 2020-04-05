//
// Created by galls2 on 04/10/19.
//

#ifndef OMG_CPP_ABSTRACT_STRUCTURE_H
#define OMG_CPP_ABSTRACT_STRUCTURE_H


#include <structures/kripke_structure.h>
#include "abstract_state.h"
class UnwindingTree;

typedef std::set<AbstractState*> AbsStateSet;

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
    AbstractState& create_astate_from_cstate(const ConcreteState& cstate);
    AbstractState& create_astate_from_astate_split(const AbstractState& astate, PropFormula sym_rep);

    EEClosureResult is_EE_closure(AbstractState& to_close , const std::set<std::reference_wrapper<AbstractState>>& close_with);
    const OmgModelChecker* get_omg() const;
    void refine_exists_successor(const ConcreteState &src_cstate, AbstractState &src_abs,
                                 const std::set<const AbstractState *> &dsts_abs);
    void refine_no_successor(const UnwindingTree& to_close_node, AbstractState& abs_src_witness, const std::set<AbstractState *> &dsts_abs);


private:
    const KripkeStructure& _kripke;
    const OmgModelChecker* _omg;
    std::set<AbstractState> _abs_states;

    std::map<AbstractState*, AbsStateSet> _NE_may;
    std::map<AbstractState*, std::vector<AbsStateSet>> _E_must;
    std::map<AbstractState*, std::vector<AbsStateSet>> _E_may_over;
    std::map<AbstractState*, std::vector<std::pair<AbsStateSet, EEClosureResult>>> _NE_may_over;

    //E MAY OVER, , NE MAY OVER
    std::pair<AbstractState*, AbstractState*> create_new_astates_and_update(AbstractState &abs_src_witness,
                                       std::pair<PropFormula, PropFormula> new_abs_state_formulas);
};


#endif //OMG_CPP_ABSTRACT_STRUCTURE_H
