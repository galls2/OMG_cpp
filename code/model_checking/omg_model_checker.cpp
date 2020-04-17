

//
// Created by galls2 on 04/10/19.
//
#include <utility>
#include <queue>
#include <unordered_set>
#include <utils/z3_utils.h>
#include "omg_model_checker.h"
#include <utils/omg_utils.h>
#include <model_checking/goal.h>

const std::map<std::string, OmgModelChecker::handler_t> OmgModelChecker::_handlers =
        {
                {"AND", &OmgModelChecker::handle_and},
                {"OR", &OmgModelChecker::handle_or},
                {"NOT", &OmgModelChecker::handle_not},
                {"XOR", &OmgModelChecker::handle_xor},
                {"ARROW", &OmgModelChecker::handle_arrow},
                {"AR", &OmgModelChecker::handle_ar},
                {"ER", &OmgModelChecker::handle_er},
                {"EX", &OmgModelChecker::handle_ex}
        };

bool OmgModelChecker::handle_and(Goal &goal)
{
        Goal first_subgoal(goal.get_node(), *goal.get_spec().get_operands()[0], goal.get_properties());
        bool first_res = recur_ctl(first_subgoal);
        if (!first_res) return false;
        Goal second_subgoal(goal.get_node(), *goal.get_spec().get_operands()[1], goal.get_properties());
        bool second_res = recur_ctl(second_subgoal);
        return second_res;
}

bool OmgModelChecker::handle_or(Goal &goal)
{
        Goal first_subgoal(goal.get_node(), *goal.get_spec().get_operands()[0], goal.get_properties());
        bool first_res = recur_ctl(first_subgoal);
        if (first_res) return true;
        Goal second_subgoal(goal.get_node(), *goal.get_spec().get_operands()[1], goal.get_properties());
        bool second_res = recur_ctl(second_subgoal);
        return second_res;
}

bool OmgModelChecker::handle_not(Goal &goal)
{
        Goal subgoal(goal.get_node(), *goal.get_spec().get_operands()[0], goal.get_properties());
        bool result = recur_ctl(subgoal);
        return !result;
}

bool OmgModelChecker::handle_xor(Goal &goal)
{
        Goal first_subgoal(goal.get_node(), *goal.get_spec().get_operands()[0], goal.get_properties());
        bool first_res = recur_ctl(first_subgoal);
        Goal second_subgoal(goal.get_node(), *goal.get_spec().get_operands()[1], goal.get_properties());
        bool second_res = recur_ctl(second_subgoal);
        return first_res ^ second_res;
}

bool OmgModelChecker::handle_arrow(Goal &goal)
{
        Goal first_subgoal(goal.get_node(), *goal.get_spec().get_operands()[0], goal.get_properties());
        bool first_res = recur_ctl(first_subgoal);
        if (!first_res) return true;
        Goal second_subgoal(goal.get_node(), *goal.get_spec().get_operands()[1], goal.get_properties());
        bool second_res = recur_ctl(second_subgoal);
        return second_res;
}

bool OmgModelChecker::handle_ar(Goal &goal)
{
    NodePriorityQueue to_visit(cmp_nodes);
    to_visit.emplace(std::ref(goal.get_node()));
    std::set<const ConcreteState*> visited;

    const CtlFormula &q = *goal.get_spec().get_operands()[1];
    const CtlFormula &p = *goal.get_spec().get_operands()[0];

    while (!to_visit.empty()) {
        UnwindingTree &node_to_explore = to_visit.top();
        to_visit.pop();
        DEBUG_PRINT_SEP; DEBUG_PRINT("AR: exploring %s\n", node_to_explore.get_concrete_state().to_bitvec_str().data());
        node_to_explore.set_urgent(false);


        // CHECK - we will delete this later. This checks for twice for the same concrete state
        assert(std::all_of(visited.begin(), visited.end(), [&](const ConcreteState *const &visitedee) {
            return node_to_explore.get_concrete_state() != (*visitedee);
        }));

        visited.emplace(&node_to_explore.get_concrete_state());

        (void) find_abs(node_to_explore);
        node_to_explore.set_developed(goal);

        Goal subgoal_q(node_to_explore, q, goal.get_properties());
        bool res_q = recur_ctl(subgoal_q);
        if (!res_q) // nte |/= q. This is the case of a refuting path!
        {
            DEBUG_PRINT("AR: Returning false due to a BUG state!\n");
            if (goal.get_properties().at("strengthen"))
            {
                handle_proving_trace(goal, node_to_explore, false);
            }
            return false;
        }

        Goal subgoal_p(node_to_explore, p, goal.get_properties());
        bool res_p = recur_ctl(subgoal_p);
        if (res_p) {
            AbstractState &astate = find_abs(node_to_explore);
            astate.add_label(true, goal.get_spec());
        } else {
            DEBUG_PRINT("AR: Unwinding successors of node: CSTATE %s depth %zu:\n", node_to_explore.get_concrete_state().to_bitvec_str().data(), node_to_explore.get_depth());
            const std::vector<std::unique_ptr<UnwindingTree>> &successors = node_to_explore.unwind_further();

            for (const std::unique_ptr<UnwindingTree> &succ : successors) {
                DEBUG_PRINT("SUCCESSOR: %s\n", succ->get_concrete_state().to_bitvec_str().data());
                if (std::all_of(visited.begin(), visited.end(), [&succ](const ConcreteState *const &visitedee) {
                    return (*visitedee) != succ->get_concrete_state();
                })) {
                    to_visit.emplace(std::ref(*succ));
                }
            }
        }


        bool inductive_res = check_inductive_av(goal, to_visit);
        if (inductive_res) {
            label_subtree(goal, true);
            return true;
        }
    }

    DEBUG_PRINT("AR: unwinding tree completely trimmed - returning TRUE!\n");

    if (goal.get_properties().at("strengthen")) {
        strengthen_subtree(goal, [goal](const UnwindingTree &n) { return n.is_developed(goal); });
        label_subtree(goal, true);
    }
    return true;

}

bool OmgModelChecker::handle_er(Goal &goal) {

    NodePriorityQueue to_visit(cmp_nodes);
    to_visit.emplace(std::ref(goal.get_node()));
    std::set<const ConcreteState *> visited;

    const CtlFormula &q = *goal.get_spec().get_operands()[1];
    const CtlFormula &p = *goal.get_spec().get_operands()[0];

    std::set<ConstAStateRef> p_satisfying_astates = _abs_structure->get_astates_by_property(p);;

    while (!to_visit.empty()) {
        UnwindingTree &node_to_explore = to_visit.top();
        to_visit.pop();
        DEBUG_PRINT_SEP;
        DEBUG_PRINT("ER: exploring %s\n", node_to_explore.get_concrete_state().to_bitvec_str().data());
        node_to_explore.set_urgent(false);

        (void) find_abs(node_to_explore);

        bool was_visited = std::any_of(visited.begin(), visited.end(), [&](const ConcreteState *const &visitedee) {
            return node_to_explore.get_concrete_state() == *visitedee;
        });

        if (was_visited) {
            if (node_to_explore.is_concrete_lasso(goal.get_node())) {
                if (goal.get_properties().at("strengthen")) {
                    handle_proving_trace(goal, node_to_explore, true);
                }
                return true;
            } else continue;
        }

        node_to_explore.set_developed(goal);

        Goal subgoal_q(node_to_explore, q, goal.get_properties());
        bool res_q = recur_ctl(subgoal_q);
        if (!res_q) // nte |/= q. This is the case of a refuting path!
        {
            DEBUG_PRINT("ER: Trimming Tree as %s |/= q!\n",
                        node_to_explore.get_concrete_state().to_bitvec_str().data());
            continue;   // This is not the druid we're looking for
        }

        visited.emplace(&node_to_explore.get_concrete_state());

        Goal subgoal_p(node_to_explore, p, goal.get_properties());
        bool res_p = recur_ctl(subgoal_p);
        if (res_p) {
            DEBUG_PRINT("ER: Returning true due to a proving trace!\n");
            if (goal.get_properties().at("strengthen")) {
                handle_proving_trace(goal, node_to_explore, true);
            }
            return true;
        } else {
            DEBUG_PRINT("ER: Unwinding successors of node: CSTATE %s depth %zu:\n",
                        node_to_explore.get_concrete_state().to_bitvec_str().data(), node_to_explore.get_depth());
            const std::vector<std::unique_ptr<UnwindingTree>> &successors = node_to_explore.unwind_further();

            for (const std::unique_ptr<UnwindingTree> &succ : successors) {
                DEBUG_PRINT("SUCCESSOR: %s\n", succ->get_concrete_state().to_bitvec_str().data());
                to_visit.emplace(std::ref(*succ));
            }
        }

        std::pair<bool, UnwindingTree *> inductive_res = check_inductive_ev(goal, node_to_explore, p_satisfying_astates);
        if (inductive_res.first) {
            throw "Implement strengthenings from check_inductive_ev from python";
        }
    }

    DEBUG_PRINT("ER: unwinding tree completely trimmed - returning FALSE!\n");
    if (goal.get_properties().at("strengthen"))
    {
        strengthen_subtree(goal, [goal](const UnwindingTree &n) { return n.is_developed(goal); });
        label_subtree(goal, false);
    }
    return false;
}

void OmgModelChecker::strengthen_subtree(Goal& goal, const std::function<bool(const UnwindingTree&)>& stop_condition)
{
    UnwindingTree& node = goal.get_node();
    const CtlFormula& spec = goal.get_spec();

    auto strengthener =
            [this](UnwindingTree& n) {
                assert(n.get_abs());
                std::set<const UnwindingTree*> dsts;
                for (auto& successor : n.get_successors()) dsts.insert(&*successor);
                refine_all_successors(n, dsts);
            };

    node.map_subtree(strengthener, stop_condition);
}


UnwindingTree& get_concretization_successor(UnwindingTree* to_close_node, const ConcreteState& dst_cstate)
{
    if (to_close_node->exist_successors())
    {
        const auto& successors = to_close_node->get_successors();
        auto res = std::find_if(successors.begin(), successors.end(),
                                [&dst_cstate](const std::unique_ptr<UnwindingTree> &successor) {
                                    return successor->get_concrete_state() == dst_cstate;
                                });
        assert(res != successors.end());
        return **res;
    }
    else
        {
        return *to_close_node;
    }
}



std::pair<bool, UnwindingTree*> OmgModelChecker::check_inductive_ev(Goal &goal, UnwindingTree &node_to_explore, const std::set<ConstAStateRef>& p_astates) {
    std::pair<CandidateSet, UnwindingTree*> abs_lasso = node_to_explore.find_abstract_lasso(goal.get_node());

    while (!abs_lasso.first.empty()) {
        assert(abs_lasso.second != nullptr);

        UnwindingTree *lasso_base = abs_lasso.second;
        const CtlFormula &p = *(goal.get_spec().get_operands()[0]);

        bool is_brother_unification = (OmgConfig::get<bool>("Brother Unification"));
        CandidateSet candidates = is_brother_unification ? brother_unification(abs_lasso.first, p) : abs_lasso.first;

        std::set<ConstAStateRef> abs_states;
        for (const auto &it : candidates) abs_states.emplace(*it.first);
        for (const auto &it : p_astates) abs_states.emplace(it);

        auto comp_ind_cands = [](const InductiveCandidate &a, const InductiveCandidate &b) {
            return a.avg_depth < b.avg_depth;
        };
        std::priority_queue<InductiveCandidate, std::vector<InductiveCandidate>, decltype(comp_ind_cands)> abs_states_lead(
                comp_ind_cands);
        for (const auto &it: candidates) {
            abs_states_lead.emplace(it.first, it.second);
        }

        while (!abs_states_lead.empty()) {
            InductiveCandidate ind_candidate = abs_states_lead.top();
            AbstractState *abs_lead = ind_candidate.abs_state;
            DEBUG_PRINT("Is there ER-inductiveness for abs state %s?... ", abs_lead->_debug_name.data());

            AEClosureResult res = _abs_structure->is_AE_closure(*abs_lead, abs_states);
            if (res.is_closed) {
                DEBUG_PRINT("Yes!\n");
                abs_states_lead.pop();
            } else {
                throw 143;
            }

        }

        if (abs_states_lead.empty()) {
            DEBUG_PRINT("ER: found ER inductiveness");
            throw 1543;
            if (goal.get_properties().at("strengthen")) {

                // strengthen trace from node to base (root to base)
                // positive label from nte to root
            }
            else
            {
                // positive label from nte to base of lasso
            }
            return {true, nullptr};
        }

        abs_lasso = node_to_explore.find_abstract_lasso(goal.get_node());
    }
    return {false, nullptr}; // Should we really do the strengthenings outside this function?
}

bool OmgModelChecker::check_inductive_av(Goal& goal, NodePriorityQueue& to_visit)
{
    CandidateSet candidates = compute_candidate_set_av(goal);

    std::set<ConstAStateRef> abs_states;
    for (const auto& it : candidates) abs_states.emplace(*it.first);

    auto comp_ind_cands = [](const InductiveCandidate& a, const InductiveCandidate& b) { return a.avg_depth < b.avg_depth; };
    std::priority_queue<InductiveCandidate, std::vector<InductiveCandidate>, decltype(comp_ind_cands)> abs_states_lead(comp_ind_cands);
    for (const auto &it: candidates) {
        if (it.first->is_neg_labeled(*goal.get_spec().get_operands()[0]))
        {
            abs_states_lead.emplace(it.first, it.second);
        }
    }

    while (!abs_states_lead.empty())
    {
        InductiveCandidate ind_candidate = abs_states_lead.top();
        AbstractState* abs_lead = ind_candidate.abs_state;
        DEBUG_PRINT("Is there AV-inductiveness for abs state %s?... ", abs_lead->_debug_name.data());

        EEClosureResult res = _abs_structure->is_EE_closure(*abs_lead, abs_states);
        if (res.is_closed)
        {
            DEBUG_PRINT("Yes!\n");
            abs_states_lead.pop();
        }
        else
        {
            DEBUG_PRINT("No!\n");
            assert(res.src); assert(res.dst);

            ConcreteState src = *(res.src), dst = *(res.dst);
            DEBUG_PRINT("CEX to AR-inductiveness: src=%s, dst=%s\n", src.to_bitvec_str().data(), dst.to_bitvec_str().data());
            AbstractState& abs_dst = find_abs(dst);

            ConcretizationResult concretization_result = is_concrete_violation(ind_candidate.nodes, abs_dst);

            if (concretization_result.dst_cstate)
            {
                DEBUG_PRINT("More unwinding due to concretization witness %s!\n", concretization_result.dst_cstate->to_bitvec_str().data());

                // More Unwinding
                const ConcreteState& dst_cstate = *concretization_result.dst_cstate;
                UnwindingTree* const to_close_node = concretization_result.src_node;

                assert(find_abs(*to_close_node).is_neg_labeled(*goal.get_spec().get_operands()[0]));

                UnwindingTree& node_to_set = get_concretization_successor(to_close_node, dst_cstate);
                node_to_set.set_urgent(true);
                to_visit.emplace(std::ref(node_to_set));

            }
            else
            {
                DEBUG_PRINT("Refinement -- no concretization witness!\n");

                AbstractState& abs_src_witness = find_abs(src);
                std::unordered_set<UnwindingTree*> to_close_nodes = ind_candidate.nodes;
                const auto& it = std::find_if(to_close_nodes.begin(), to_close_nodes.end(),
                        [this, abs_src_witness](UnwindingTree* n) {
                    AbstractState& current = find_abs(*n);
                 //   DEBUG_PRINT("%s vs %s\n", current._debug_name.c_str(), abs_src_witness._debug_name.c_str());
                    return find_abs(*n) == abs_src_witness; } );
                if (it == to_close_nodes.end()) throw OmgMcException("ERROR -- BUG IN INDUCTIVENESS!");

                UnwindingTree* to_close_node = *it;

                refine_no_successor(*to_close_node, abs_src_witness, abs_dst);
            }

            return false;
        }
    }
    DEBUG_PRINT("Found EE-inductiveness!\n");
    return true;
}

CandidateSet OmgModelChecker::compute_candidate_set_av(Goal &goal)
{
    CandidateSet cands;
    UnwindingTree& root = goal.get_node();
    auto inserter = [&cands] (UnwindingTree& node)
    {
        auto abs = node.get_abs();
        assert(abs);

        AbstractState* p_abs = &(abs->get());
        cands[p_abs].emplace(&node);
    };

    root.map_subtree(inserter, [&goal](const UnwindingTree &node) {
        return node.is_developed(goal);
    });

    if (OmgConfig::get<bool>("Brother Unification"))
        return brother_unification(cands, *(goal.get_spec().get_operands()[0]));
    else return cands;
}

void unify_same_level(CandidateSet& src, const CtlFormula& agree_upon, CandidateSet& unchanged, CandidateSet& next_level)
{
    std::map<const AbstractClassificationNode *, std::pair<AbstractState*, std::vector<std::unordered_set<UnwindingTree*>>>> parents_mapping;

    for (const std::pair<AbstractState* const, std::unordered_set<UnwindingTree*>>& it : src) {
        const AbstractClassificationNode* parent = it.first->get_cl_node()->get_parent();
        assert(parent != nullptr);
        parents_mapping[parent].second.push_back(it.second);
        parents_mapping[parent].first = it.first;
    }

    for (const std::pair<const AbstractClassificationNode* const, std::pair<AbstractState*, std::vector<std::unordered_set<UnwindingTree*>>>> &it : parents_mapping)
    {
        if (it.second.second.size() == 2)
        {
            AbstractState* new_abs = it.first->get_abs();

            std::unordered_set<UnwindingTree*> new_set;
            for (const auto& p_cand : it.second.second) {
                new_set.insert(p_cand.begin(), p_cand.end());
            }
            next_level.emplace(new_abs, new_set);
        }
        else
        {
            assert(it.second.second.size() == 1);
            unchanged.emplace(it.second.first, it.second.second[0]);
        }
    }
}

CandidateSet OmgModelChecker::brother_unification(const CandidateSet &cands, const CtlFormula& agree_upon)
{
    std::map<size_t, CandidateSet> levels;
    size_t max_depth = cands.begin()->first->get_cl_node()->get_depth();
    for (const std::pair<AbstractState* const, std::unordered_set<UnwindingTree*>>& it : cands)
    {
        size_t depth = it.first->get_cl_node()->get_depth();
        max_depth = max_depth >= depth ? max_depth : depth;
        levels[depth].emplace(it);
    }

    CandidateSet reduced;
    for (size_t depth = max_depth; depth > 0; --depth)
    {
        if (levels.find(depth) == levels.end() || levels[depth].empty()) continue;

        CandidateSet unchanged, next_level;
        unify_same_level(levels[depth], agree_upon, unchanged, next_level);

        reduced.insert(unchanged.begin(), unchanged.end());

        size_t next_depth = depth - 1;
        levels[next_depth].insert(next_level.begin(), next_level.end());
    }

    if (levels.find(0) != levels.end()) reduced.insert(levels[0].begin(), levels[0].end());

    return reduced;
}



bool OmgModelChecker::handle_ex(Goal &goal)
{
    CtlFormula& subformula = *goal.get_spec().get_operands()[0];
    const std::vector<std::unique_ptr<UnwindingTree>> &successors = goal.get_node().unwind_further();
    for (auto& successor : successors)
    {
        DEBUG_PRINT("EX: exploring %s\n", successor->get_concrete_state().to_bitvec_str().data());
        Goal subgoal(*successor, subformula, goal.get_properties());
        bool res = recur_ctl(subgoal);
        if (res) {
            DEBUG_PRINT("EX: found a satisfying successor %s\n", successor->get_concrete_state().to_bitvec_str().data());
            if (goal.get_properties().at("strengthen"))
            {
                refine_exists_successor(goal.get_node(), {&successor->get_concrete_state()});
            }
            return true;
        }
    }

    DEBUG_PRINT("EX: no satisfying successor found!\n");
    if (goal.get_properties().at("strengthen"))
    {
        std::set<const UnwindingTree*> dst_nodes;
        for (const auto& succ : successors) dst_nodes.insert(&*succ);
        refine_all_successors(goal.get_node(), dst_nodes);
    }
    return false;


}

OmgModelChecker::OmgModelChecker(const KripkeStructure &kripke) : _kripke(kripke)
{
        initialize_abstraction();
}

void OmgModelChecker::initialize_abstraction()
{
        _abs_structure = std::make_unique<AbstractStructure>(_kripke, this);
        _abs_classifier = std::make_unique<AbstractionClassifier>(_kripke);
}

bool OmgModelChecker::model_checking(ConcreteState &cstate, const CtlFormula &specification)
{
    // In the future - unwinding tree cache is to be used here
    std::unique_ptr<UnwindingTree> root = std::make_unique<UnwindingTree>(_kripke, cstate, nullptr);

    root->reset_developed_in_tree();

    Goal goal(*root, specification, {{"strengthen", true}});
    bool result = recur_ctl(goal);
    return result;
}

bool OmgModelChecker::recur_ctl(Goal &g)
{
        const CtlFormula& spec = g.get_spec();

        if (spec.is_boolean())
        {
            return spec.get_boolean_value();
        }

        AbstractState& astate = find_abs(g.get_node());

        if (astate.is_pos_labeled(spec)) return true;
        if (astate.is_neg_labeled(spec)) return false;

        assert(!spec.get_operands().empty());
        std::string main_connective = spec.get_data();
        handler_t handler = _handlers.at(main_connective);
        bool result = (this->*handler)(g);

        if (g.get_properties().at("strengthen"))
        {
                astate.add_label(result, spec);
        }

        return result;
}


AbstractState &OmgModelChecker::find_abs(UnwindingTree &node)
{
    const ConcreteState& cstate = node.get_concrete_state();
    if (node.get_abs())
    {
        AbstractState &astate = *node.get_abs();
        if (astate.is_final_classification())
        {
            return astate;
        }
        else
        {
            AbstractState &updated_abs = _abs_classifier->update_classification(astate, cstate);
            node.set_abs(updated_abs);
            return updated_abs;
        }
    }
    else
    {
        AbstractState &astate = find_abs(cstate);
        node.set_abs(astate);
        return astate;
    }
}

AbstractState &OmgModelChecker::find_abs(const ConcreteState &cstate)
{
    if (!_abs_classifier->exists_classification(cstate))
    {
        AbstractState &astate = _abs_structure->create_astate_from_cstate(cstate);
        _abs_classifier->add_classification_tree(cstate, astate);
        return astate;
    }
    else
    {
        AbstractState& abs = _abs_classifier->classify(cstate);
        return abs;
    }
}

void OmgModelChecker::handle_proving_trace(Goal &goal, UnwindingTree &node, bool positivity)
{
    const CtlFormula &spec = goal.get_spec();
    strengthen_trace(goal.get_node(), node);
    node.map_upwards(
            [&spec, positivity](UnwindingTree &n) { n.add_label(positivity, spec); },
            [](const UnwindingTree &m) { return m.get_parent() == nullptr; }
    );
}

void OmgModelChecker::label_subtree(Goal &goal, bool positivity) {
    UnwindingTree& node = goal.get_node();
    const CtlFormula& spec = goal.get_spec();

    auto labeler =
                 [positivity, &spec](UnwindingTree& n) {
                     assert(n.get_abs());
                     n.get_abs()->get().add_label(positivity, spec);
                 };
    auto activation_condition = [&goal](const UnwindingTree& m) { return m.is_developed(goal); };

    node.map_subtree(labeler, activation_condition);
}

ConcretizationResult
OmgModelChecker::is_concrete_violation(const std::unordered_set<UnwindingTree *> &to_close_nodes,
                                       AbstractState &abs_witness)
{
    return FormulaInductiveUtils::concrete_transition_to_abs(to_close_nodes, abs_witness);
}

void OmgModelChecker::strengthen_trace(UnwindingTree &start, UnwindingTree &end)
{
    UnwindingTree* current = &end;
    std::set<const ConcreteState*> dsts;
    while (current != &start)
    {
        dsts.emplace(&current->get_concrete_state());
        refine_exists_successor(*current->get_parent(), dsts);
        current = current->get_parent();
    }
}

void OmgModelChecker::refine_exists_successor(UnwindingTree& src_node,
                                              const std::set<const ConcreteState *> &dsts_cstate)
{
    ConstAbsStateSet dsts_abs;
    for (const ConcreteState* dst_cstate : dsts_cstate) dsts_abs.insert(&find_abs(*dst_cstate));

    AbstractState& src_abs = find_abs(src_node.get_concrete_state());


    RefinementResult refinement_res = _abs_structure->refine_exists_successor(src_node.get_concrete_state(), src_abs, dsts_abs, true);

    update_classifier(refinement_res, src_abs);
    find_abs(src_node); // redundant?
}

void OmgModelChecker::update_classifier(RefinementResult& refine_result, AbstractState& abs_src_witness) {
    if (!refine_result.is_split) return;

    _abs_classifier->split(abs_src_witness, *refine_result.split_query, *refine_result.astate_generalized, *refine_result.astate_remainder);

    refine_result.astate_generalized->set_cl_node(&abs_src_witness.get_cl_node()->get_successor(true));
    refine_result.astate_remainder->set_cl_node(&abs_src_witness.get_cl_node()->get_successor(false));

    DEBUG_PRINT("<<<TODO>>> NEED To IMPL CLASSIFICATION CACHE!\n");

}

void OmgModelChecker::refine_no_successor(UnwindingTree &to_close_node, AbstractState &abs_src_witness,
                                          AbstractState &abs_dst)
{
    /*
     * One might have thought that we can use here EX+ refinement with the state that we found that does have a transition to
     * absssss_dst in order to conduct the split, instead of this EX- refinement that we conduct.
     * However, this is not ture. he reason is that we want to split AWAY the part of abs_src_witness that includes the reacehable
     * node in the unwinding tree, which is not necessarily done in EX+.
     */
    RefinementResult refine_res = _abs_structure->refine_no_successor(to_close_node, abs_src_witness, {&abs_dst}, false);
    update_classifier(refine_res, abs_src_witness);
    find_abs(to_close_node); // redundant?
}

void OmgModelChecker::refine_all_successors(UnwindingTree& to_close_node, const std::set<const UnwindingTree*>& dsts_nodes)
{
    ConstAbsStateSet dsts_abs;
    for (const UnwindingTree* dst_node : dsts_nodes) dsts_abs.insert(&find_abs(dst_node->get_concrete_state()));

    AbstractState& abs_src_witness = find_abs(to_close_node);


    RefinementResult refine_res = _abs_structure->refine_all_successors(to_close_node, abs_src_witness, dsts_abs, true);
    update_classifier(refine_res, abs_src_witness);
    find_abs(to_close_node); // redundant?
}



InductiveCandidate::InductiveCandidate(AbstractState *_abs_state, std::unordered_set<UnwindingTree *> _nodes)
    : abs_state(_abs_state), nodes(std::move(_nodes))
{
    avg_depth = ((double) std::accumulate(_nodes.begin(), _nodes.end(), 0U,
            [] (size_t partial_sum, UnwindingTree* node) {  return node->get_depth() + partial_sum; } ) ) / _nodes.size();
}