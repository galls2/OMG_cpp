
#pragma once
//
// Created by galls2 on 04/10/19.
//
#include <utility>
#include "goal.h"
#include <unordered_map>
#include <unordered_set>
#include <structures/kripke_structure.h>
#include <abstraction/abstract_structure.h>
#include <abstraction/abstraction_classifier.h>
#include <structures/unwinding_tree.h>
#include <configuration/omg_config.h>

DECLARE_OMG_EXCEPTION(OmgMcException)

class UnwindingTree;


typedef std::unordered_map<AbstractState*, std::unordered_set<UnwindingTree*>> CandidateSet;

struct InductiveCandidate
{
    AbstractState* abs_state;
    std::unordered_set<UnwindingTree*> nodes;
    double avg_depth;
    InductiveCandidate(AbstractState* _abs_state, std::unordered_set<UnwindingTree*> _nodes);
};

struct ConcretizationResult
{
    explicit ConcretizationResult(UnwindingTree* const src_node_ = nullptr, std::experimental::optional<ConcreteState> dst_cstate = {})
    : src_node(src_node_), dst_cstate(std::move(dst_cstate)) {}
    UnwindingTree* const src_node;
    std::experimental::optional<ConcreteState> dst_cstate;
};

class OmgModelChecker {
public:
    explicit OmgModelChecker(KripkeStructure& kripke);

    typedef bool (OmgModelChecker::*handler_t)(Goal& goal);
    bool model_checking(const ConcreteState& cstate, const CtlFormula& specification);
    bool check_all_initial_states(const CtlFormula& specification);


private:
    KripkeStructure& _kripke;
    std::unique_ptr<AbstractStructure> _abs_structure;
    std::unique_ptr<AbstractionClassifier> _abs_classifier;
   // std::map_subtree<std::unique_ptr<UnwindingTree>> _unwinding_trees;



    /*
     * Model Checking
     */
    bool recur_ctl(Goal& g);

    /*
     * Handlers
     */
    bool handle_and(Goal& goal);
    bool handle_or(Goal& goal);
    bool handle_not(Goal& goal);
    bool handle_equiv(Goal& goal);
    bool handle_xor(Goal& goal);
    bool handle_arrow(Goal& goal);
    bool handle_ar(Goal& goal);
    bool handle_er(Goal& goal);
    bool handle_ex(Goal& goal);

    void initialize_abstraction();

    AbstractState& find_abs(UnwindingTree& node);
    AbstractState& find_abs(const ConcreteState& node);
    static const std::map<std::string, handler_t> _handlers;

    bool check_inductive_av(Goal& goal, NodePriorityQueue& to_visit);
    bool check_inductive_ev(Goal& goal, UnwindingTree& node_to_explore, const std::set<ConstAStateRef>& p_astates);
    void strengthen_subtree(Goal& goal, const std::function<bool(const UnwindingTree&)>& stop_condition);
    void strengthen_trace(UnwindingTree& start, UnwindingTree& end);
    void handle_proving_trace(Goal& goal, UnwindingTree& node_to_explore, bool positivity);
    CandidateSet compute_candidate_set_av(Goal &goal);
    CandidateSet brother_unification(const CandidateSet &cands, const CtlFormula& agree_upon);
    void label_subtree(Goal& goal, bool positivity);

    ConcretizationResult
    is_concrete_violation(const std::unordered_set<UnwindingTree *> &to_close_nodes, AbstractState &abs_witness);

    void refine_exists_successor(UnwindingTree& src_node, const ConstAbsStateSet& dsts_abs);
    void refine_exists_successor(UnwindingTree& src_node, const std::set<const ConcreteState*>& dsts_abs);
    void refine_no_successor(UnwindingTree& to_close_node, AbstractState& abs_src_witness, AbstractState& abs_dst);
    void refine_all_successors(UnwindingTree& to_close_node, const std::set<const UnwindingTree*>& dsts_nodes);

    void update_classifier(RefinementResult& refine_result, AbstractState& abs_src_witness);
};

