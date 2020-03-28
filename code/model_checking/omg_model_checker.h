
#pragma once
//
// Created by galls2 on 04/10/19.
//
#include <utility>

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
    InductiveCandidate(AbstractState* _abs_state, std::unordered_set<UnwindingTree*> _nodes) : abs_state(_abs_state), nodes(
            std::move(_nodes))
    {
        double avg = 0;
        for (UnwindingTree* const& node : nodes)
            avg += node->get_depth();
        avg /= nodes.size();
        avg_depth = avg;
    }
};

struct ConcretizationResult
{
    explicit ConcretizationResult(UnwindingTree* const src_node_, std::experimental::optional<ConcreteState> dst_cstate = std::experimental::optional<ConcreteState>())
    : src_node(src_node_), dst_cstate(std::move(dst_cstate)) {}
    UnwindingTree* const src_node;
    std::experimental::optional<ConcreteState> dst_cstate;
};

class OmgModelChecker {
public:


    typedef bool (OmgModelChecker::*handler_t)(Goal& goal);
    bool model_checking(ConcreteState& cstate, const CtlFormula& specification);

    OmgModelChecker(const KripkeStructure& kripke, const OmgConfiguration& config);

    /*
    * Configurable Properties
    */
    const bool _opt_trivial_splits; // Is the Trivial Split Elimination optimization activated
    const bool _opt_brother_unif; // Is the Trivial Split Elimination optimization activated
    const std::string _sat_solver; // What SAT solver to use

private:
    const KripkeStructure& _kripke;
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
    void strengthen_subtree(Goal& goal, const std::function<bool(const UnwindingTree&)>& stop_condition);
    void strengthen_trace(UnwindingTree& start, UnwindingTree& end) const;
    void handle_proving_trace(bool is_strengthen, Goal& goal, UnwindingTree& node_to_explore, bool positivity);
    CandidateSet compute_candidate_set(Goal& goal, bool brother_unif);
    CandidateSet brother_unification(const CandidateSet &cands, const CtlFormula& agree_upon);
    void label_subtree(Goal& goal, bool positivity);

    ConcretizationResult
    is_concrete_violation(const std::unordered_set<UnwindingTree *> &to_close_nodes, AbstractState &abs_witness);

    void refine_exists_successor(const ConcreteState* src_cstate, const std::set<const ConcreteState*>& dsts_cstate);

    void update_classifier();
};

