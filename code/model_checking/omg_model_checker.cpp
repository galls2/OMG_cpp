

//
// Created by galls2 on 04/10/19.
//
#include <numeric>
#include <utility>
#include <queue>
#include <unordered_set>
#include <utils/z3_utils.h>
#include "omg_model_checker.h"
#include <utils/omg_utils.h>
#include <model_checking/goal.h>
#include <utils/Stats.h>

using namespace avy;

const std::map<std::string, OmgModelChecker::handler_t> OmgModelChecker::_handlers =
        {
                {"AND", &OmgModelChecker::handle_and},
                {"OR", &OmgModelChecker::handle_or},
                {"NOT", &OmgModelChecker::handle_not},
                {"XOR", &OmgModelChecker::handle_xor},
                {"ARROW", &OmgModelChecker::handle_arrow},
                {"AR", &OmgModelChecker::handle_ar},
                {"ER", &OmgModelChecker::handle_er},
                {"EX", &OmgModelChecker::handle_ex},
                {"EQUIV", &OmgModelChecker::handle_equiv}
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

    DEBUG_PRINT("AR: checking %s\n",goal.to_string().data());
    NodePriorityQueue to_visit(cmp_nodes);
#ifdef DEBUG
    size_t prev_size = to_visit.size();
#endif
    to_visit.emplace(&goal.get_node());
#ifdef DEBUG
    assert(to_visit.size() == prev_size + 1);
#endif
    std::set<const ConcreteState*> visited;

    const CtlFormula &q = *goal.get_spec().get_operands()[1];
    const CtlFormula &p = *goal.get_spec().get_operands()[0];

    while (!to_visit.empty()) {

#ifdef DEBUG
        bool exist_urgent = false;
        for (const auto& it : to_visit) {
            if (it->is_urgent())
            {
                assert(!exist_urgent);
                exist_urgent = true;
            }
//            for (const auto &it2 : to_visit) {
//                assert((it == it2) || (it->get_concrete_state() != it2->get_concrete_state()));
//            }
        }

//        for (const auto& it_visited : visited)
//            for (const auto& it_to_visit : to_visit)
//            {
//                assert(it_to_visit->get_concrete_state() != *it_visited);
//            }
#endif

        UnwindingTree &node_to_explore = **to_visit.begin();
        size_t res = to_visit.erase(&node_to_explore); // why doesn't this work by value?
        assert(res == 1);

#ifdef DEBUG
        assert(exist_urgent == node_to_explore.is_urgent());
#endif

        DEBUG_PRINT_SEP; DEBUG_PRINT("AR: exploring %s\n", node_to_explore.get_concrete_state().to_bitvec_str().data());
        node_to_explore.set_urgent(false);
        assert(std::none_of(to_visit.begin(), to_visit.end(), [] (const UnwindingTree* n) { return n->is_urgent();}));

        if (std::any_of(visited.begin(), visited.end(), [&](const ConcreteState *const &visitedee) {
            return node_to_explore.get_concrete_state() == (*visitedee);
        }))
        {
            DEBUG_PRINT("AR: already visited. Skipping.\n");
            continue;
        }

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
            DEBUG_PRINT("Node satisfies p - not developing successors!\n");
            AbstractState &astate = find_abs(node_to_explore);
            astate.add_label(true, goal.get_spec());
        } else {
            DEBUG_PRINT("AR: Unwinding successors of node: CSTATE %s depth %zu:\n", node_to_explore.get_concrete_state().to_bitvec_str().data(), node_to_explore.get_depth());
            const std::vector<std::unique_ptr<UnwindingTree>> &successors = node_to_explore.unwind_further();

            for (const std::unique_ptr<UnwindingTree> &succ : successors) {
        //        DEBUG_PRINT("SUCCESSOR: %s\n", succ->get_concrete_state().to_bitvec_str().data());
                if (std::all_of(visited.begin(), visited.end(), [&succ](const ConcreteState *const &visitedee) {
                    return (*visitedee) != succ->get_concrete_state();
                })) {
                    to_visit.emplace(succ.get());
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
#ifdef DEBUG
    size_t prev_size = to_visit.size();
#endif
    to_visit.emplace(&goal.get_node());
#ifdef DEBUG
    assert(to_visit.size() == prev_size + 1);
#endif
    std::set<const ConcreteState *> visited;

    const CtlFormula &q = *goal.get_spec().get_operands()[1];
    const CtlFormula &p = *goal.get_spec().get_operands()[0];

    std::set<ConstAStateRef> p_satisfying_astates = _abs_structure->get_astates_by_property(p);;

    while (!to_visit.empty()) {
#ifdef DEBUG
        bool exist_urgent = false;
        for (const auto& it : to_visit) {
            if (it->is_urgent())
            {
                assert(!exist_urgent);
                exist_urgent = true;
            }
//            for (const auto &it2 : to_visit) {
//                assert((it == it2) || (it->get_concrete_state() != it2->get_concrete_state()));
//            }
        }
#endif

        UnwindingTree &node_to_explore = **to_visit.begin();
        size_t res = to_visit.erase(&node_to_explore);
        assert(res == 1);

#ifdef DEBUG
        assert(exist_urgent == node_to_explore.is_urgent());
#endif

        DEBUG_PRINT_SEP;
        DEBUG_PRINT("ER: exploring %s\n", node_to_explore.get_concrete_state().to_bitvec_str().data());
        node_to_explore.set_urgent(false);
        assert(std::none_of(to_visit.begin(), to_visit.end(), [] (const UnwindingTree* n) { return n->is_urgent();}));

        (void) find_abs(node_to_explore);

        bool was_visited = std::any_of(visited.begin(), visited.end(), [&](const ConcreteState *const &visitedee) {
            return node_to_explore.get_concrete_state() == *visitedee;
        });

        if (was_visited) {
            if (node_to_explore.is_concrete_lasso(goal.get_node())) {
            DEBUG_PRINT("ER: Found CONCRETE lasso with the base %s!\n", node_to_explore.get_concrete_state().to_bitvec_str().data());
                node_to_explore.is_concrete_lasso(goal.get_node());
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
      //          DEBUG_PRINT("SUCCESSOR: %s\n", succ->get_concrete_state().to_bitvec_str().data());
                to_visit.emplace(succ.get());
            }
        }

        bool inductive_res = check_inductive_ev(goal, node_to_explore, p_satisfying_astates);
        if (inductive_res) {
            return true;
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

    auto strengthener =
            [this](UnwindingTree& n) {
                assert(n.get_abs() && n.get_abs()->get().is_final_classification());
                std::set<const UnwindingTree*> dsts;
                for (auto& successor : n.get_successors()) dsts.insert(&*successor);
                refine_all_successors(n, dsts);
            };

    node.map_subtree(strengthener, stop_condition);
}


UnwindingTree& get_concretization_successor(UnwindingTree* to_close_node, const ConcreteState& dst_cstate)
{
    AVY_MEASURE_FN;

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



bool OmgModelChecker::check_inductive_ev(Goal &goal, UnwindingTree &node_to_explore, const std::set<ConstAStateRef>& p_astates) {
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

        InductiveCandidatePriorityQueue  abs_states_lead(comp_ind_cands);
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
                assert(res.violator);
                ConcreteState& src = *res.violator;

                DEBUG_PRINT("No! Found cex: %s\n", src.to_bitvec_str().data());

                AbstractState& abs_src_witness = find_abs(src);

                std::unordered_set<UnwindingTree*> to_close_nodes = ind_candidate.nodes;
                const auto& it = std::find_if(to_close_nodes.begin(), to_close_nodes.end(),
                                              [this, &abs_src_witness](UnwindingTree* n) {
//                                                  AbstractState& current = find_abs(*n);
                                                  //   DEBUG_PRINT("%s vs %s\n", current._debug_name.c_str(), abs_src_witness._debug_name.c_str());
                                                  return find_abs(*n) == abs_src_witness; } );
                if (it == to_close_nodes.end()) throw OmgMcException("ERROR -- BUG IN INDUCTIVENESS!");

                UnwindingTree* to_close_node = *it;

                ConstAbsStateSet abs_states_to_send;
                for (const auto& iter : abs_states) abs_states_to_send.emplace(&iter.get());
                refine_exists_successor(*to_close_node, abs_states_to_send);

            }

        }

        if (abs_states_lead.empty()) {
            DEBUG_PRINT("ER: found ER inductiveness!\n");
            if (goal.get_properties().at("strengthen")) {
                strengthen_trace(goal.get_node(), *lasso_base);
                node_to_explore.map_upwards([&goal] (UnwindingTree& n) {  n.add_label(true, goal.get_spec()); },
                        [&goal] (const UnwindingTree& n) {return &n == &goal.get_node(); });
            }
            else
            {
                node_to_explore.map_upwards([&goal] (UnwindingTree& n) {  n.add_label(true, goal.get_spec()); },
                                            [&lasso_base] (const UnwindingTree& n) {return &n == lasso_base; });
            }
            return true;
        }

        abs_lasso = node_to_explore.find_abstract_lasso(goal.get_node());
    }
    return false;
}

bool OmgModelChecker::check_inductive_av(Goal& goal, NodePriorityQueue& to_visit)
{
    AVY_MEASURE_FN;

    CandidateSet candidates = compute_candidate_set_av(goal);

    std::set<ConstAStateRef> abs_states;
    for (const auto& it : candidates) abs_states.emplace(*it.first);

    InductiveCandidatePriorityQueue abs_states_lead(comp_ind_cands);

    AbsStateSet astates_lead_to_formula_skeleton;
    for (const auto &it: candidates) {
        if (it.first->is_neg_labeled(*goal.get_spec().get_operands()[0]))
        {
            abs_states_lead.emplace(it.first, it.second);
            astates_lead_to_formula_skeleton.emplace(it.first); //
        }
    }
    std::map<const AbstractState*, z3::expr> astate_flags;
//      std::unique_ptr<ISatSolver> solver = ISatSolver::s_solvers.at(OmgConfig::get<std::string>("Sat Solver"))(candidates.begin()->first->get_formula().get_ctx()); //
    PropFormula skeleton = FormulaInductiveUtils::create_EE_inductive_formula_skeleton(astates_lead_to_formula_skeleton, abs_states, astate_flags); //

    while (!abs_states_lead.empty())
    {
        InductiveCandidate ind_candidate = abs_states_lead.top();
        AbstractState* abs_lead = ind_candidate.abs_state;
        DEBUG_PRINT("Is there AV-inductiveness for abs state %s?... ", abs_lead->_debug_name.data());

        EEClosureResult res = _abs_structure->is_EE_closure2(skeleton, *abs_lead, abs_states, *_tr_sat_solver, astate_flags); //

//        EEClosureResult res = _abs_structure->is_EE_closure(*abs_lead, abs_states); //
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

                // More Unwinding
                const ConcreteState& dst_cstate = *concretization_result.dst_cstate;
                UnwindingTree* const to_close_node = concretization_result.src_node;

                DEBUG_PRINT("More unwinding due to concretization witness transition ([%s], [%s])!\n", to_close_node->get_concrete_state().to_bitvec_str().data(), dst_cstate.to_bitvec_str().data());


                assert(find_abs(*to_close_node).is_neg_labeled(*goal.get_spec().get_operands()[0]));

                UnwindingTree& node_to_set = get_concretization_successor(to_close_node, dst_cstate);
                DEBUG_PRINT("Node to set URGENT (supposed to be explored next): %s\n", node_to_set.get_concrete_state().to_bitvec_str().data());

                to_visit.erase(&node_to_set);
         //       assert(erase_res == 1); // We don't care as node_to_set may not be here, as it was developed for a subgoal
                node_to_set.set_urgent(true);
#ifdef DEBUG
                size_t prev_size = to_visit.size();
#endif
                to_visit.emplace(&node_to_set);
#ifdef DEBUG
                assert(to_visit.size() == prev_size + 1);
#endif
            }
            else
            {
                DEBUG_PRINT("Refinement -- no concretization witness!\n");

                AbstractState& abs_src_witness = find_abs(src);

                DEBUG_PRINT("Finding a node that corresponds to %s\n", abs_src_witness._debug_name.data());

                std::unordered_set<UnwindingTree*> to_close_nodes = ind_candidate.nodes;
                const auto& it = std::find_if(to_close_nodes.begin(), to_close_nodes.end(),
                        [this, &abs_src_witness](UnwindingTree* n) {
//                    AbstractState& current = find_abs(*n);
                 //   DEBUG_PRINT("%s vs %s\n", current._debug_name.c_str(), abs_src_witness._debug_name.c_str());
                    return find_abs(*n) == abs_src_witness; } );
                if (it == to_close_nodes.end()) {
#ifdef DEBUG
                    DEBUG_PRINT("Found bug in inductiveness! to_close_nodes:\n");
                    for (UnwindingTree* n : to_close_nodes)
                    {
                        DEBUG_PRINT("\t %s : %s\n", n->to_string().data(), find_abs(*n)._debug_name.data());
                    }
#endif
                    throw OmgMcException("ERROR -- BUG IN INDUCTIVENESS!");
                }
                UnwindingTree* to_close_node = *it;

                assert(find_abs(*to_close_node) == abs_src_witness);
                DEBUG_PRINT("Found %s!\n", to_close_node->to_string().data());

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
    AVY_MEASURE_FN;

    CandidateSet cands;
    UnwindingTree& root = goal.get_node();
    auto inserter = [this, &cands] (UnwindingTree& node)
    {
        assert(node.get_abs()); // Check that a classification exists, even if not up to date
        AbstractState& abs = find_abs(node);
        cands[&abs].emplace(&node);
    };

    root.map_subtree(inserter, [&goal](const UnwindingTree &node) {
        return node.is_developed(goal);
    });

#ifdef DEBUG
    for (const auto& it : cands)
    {
        assert(it.first->is_final_classification());
        for (const auto& it2 : it.second)
        {
            assert(it2->get_abs());
            assert(it2->get_abs()->get().is_final_classification());
            assert(it2->get_abs()->get() == *it.first);
        }
    }
#endif
    if (OmgConfig::get<bool>("Brother Unification"))
        return brother_unification(cands, *(goal.get_spec().get_operands()[0]));
    else return cands;
}

bool is_successors_agree(const AbstractClassificationNode* cl_node, const CtlFormula& f)
{
    const AbstractState* astate1 = cl_node->get_successor(true).get_abs();
    const AbstractState* astate2 = cl_node->get_successor(false).get_abs();

    bool is_first_pos = astate1->is_pos_labeled(f);
    bool is_second_pos = astate2->is_pos_labeled(f);
    bool is_first_neg = astate1->is_neg_labeled(f);
    bool is_second_neg = astate2->is_neg_labeled(f);
    if ((is_first_neg && is_second_neg) || (is_first_pos && is_second_pos)) return true;
    bool is_first_labeled = is_first_pos || is_first_neg;
    bool is_second_labeled = is_second_neg || is_second_pos;
    return (!is_first_labeled && !is_second_labeled);
}
void unify_same_level(CandidateSet& src, const CtlFormula& agree_upon, CandidateSet& unchanged, CandidateSet& next_level)
{
    std::map<const AbstractClassificationNode *, std::vector<std::pair<AbstractState*, std::unordered_set<UnwindingTree*>>>> parents_mapping;

    for (const std::pair<AbstractState* const, std::unordered_set<UnwindingTree*>>& it : src) {
        const AbstractClassificationNode* parent = it.first->get_cl_node()->get_parent();
        assert(parent != nullptr);
        parents_mapping[parent].emplace_back(it.first, it.second);
    }

    for (const std::pair<const AbstractClassificationNode* const, std::vector<std::pair<AbstractState*, std::unordered_set<UnwindingTree*>>>> &it : parents_mapping)
    {
        if (it.second.size() == 2 && is_successors_agree(it.first, agree_upon)) {
            assert(!it.first->get_abs()->get_cl_node()->is_leaf());
            AbstractState *new_abs = it.first->get_abs();

            std::unordered_set<UnwindingTree *> new_set;
            for (const auto &p_cand : it.second) {
                new_set.insert(p_cand.second.begin(), p_cand.second.end());
            }
            next_level.emplace(new_abs, new_set);

        }
        else
        {
            assert(it.second.size() <= 2 && it.second.size() >= 1);
            for (const auto &i : it.second) unchanged.emplace(i.first, i.second);
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
            DEBUG_PRINT("EX: found a satisfying successor %s - returning TRUE\n", successor->get_concrete_state().to_bitvec_str().data());
            if (goal.get_properties().at("strengthen"))
            {
                strengthen_trace(goal.get_node(), *successor);
            }
            return true;
        }
    }

    DEBUG_PRINT("EX: no satisfying successor found! -- returning FALSE\n");
    if (goal.get_properties().at("strengthen"))
    {
        std::set<const UnwindingTree*> dst_nodes;
        for (const auto& succ : successors) dst_nodes.insert(&*succ);
        refine_all_successors(goal.get_node(), dst_nodes);
    }
    return false;


}

OmgModelChecker::OmgModelChecker(KripkeStructure &kripke) : _kripke(kripke)
{
        initialize_abstraction();
        _tr_sat_solver = ISatSolver::s_solvers.at(OmgConfig::get<std::string>("Sat Solver"))(kripke.get_tr().get_ctx());
        _tr_sat_solver->add(_kripke.get_tr().get_raw_formula());
}

void OmgModelChecker::initialize_abstraction()
{
        _abs_structure = std::make_unique<AbstractStructure>(_kripke, this);
        _abs_classifier = std::make_unique<AbstractionClassifier>(_kripke);
}

bool OmgModelChecker::check_all_initial_states(const CtlFormula& specification)
{
    std::vector<ConcreteState> inits = _kripke.get_initial_states();

    for (ConcreteState& it : inits)
    {
        DEBUG_PRINT("Checking initial state: %s\n", it.to_bitvec_str().data());
        bool result = model_checking(it, specification);
        if (!result) return false;
    }

    return true;
}

bool OmgModelChecker::model_checking(ConcreteState &cstate, const CtlFormula &specification)
{
//    std::cout << specification.to_string() << std::endl;
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
    AVY_MEASURE_FN;

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
    AVY_MEASURE_FN;

    if (!_abs_classifier->exists_classification(cstate))
    {
        AbstractState &astate = _abs_structure->create_astate_from_cstate(cstate);
        _abs_classifier->add_classification_tree(cstate, astate);
        return astate;
    }
    else
    {
        AbstractState& abs = _abs_classifier->classify_cstate(cstate);
        return abs;
    }
}

void OmgModelChecker::handle_proving_trace(Goal &goal, UnwindingTree &node, bool positivity)
{
    const CtlFormula &spec = goal.get_spec();
    strengthen_trace(goal.get_node(), node);
    node.map_upwards(
            [this, &spec, positivity](UnwindingTree &n) {
                AbstractState& astate = find_abs(n);
                astate.add_label(positivity, spec);
                },
            [&goal](const UnwindingTree &m) { return &m ==  &goal.get_node(); }
    );
}

void OmgModelChecker::label_subtree(Goal &goal, bool positivity) {
    UnwindingTree& node = goal.get_node();
    const CtlFormula& spec = goal.get_spec();

    auto labeler =
                 [this, positivity, &spec](UnwindingTree& n) {
                    AbstractState& astate = find_abs(n);
                    astate.add_label(positivity, spec);
                 };
    auto activation_condition = [&goal](const UnwindingTree& m) { return m.is_developed(goal); };

    node.map_subtree(labeler, activation_condition);
}

ConcretizationResult
OmgModelChecker::is_concrete_violation(const std::unordered_set<UnwindingTree *> &to_close_nodes,
                                       AbstractState &abs_witness)
{
    AVY_MEASURE_FN;
//    auto sat_solver = ISatSolver::s_solvers.at(OmgConfig::get<std::string>("Sat Solver"))(abs_witness.get_formula().get_ctx());
    auto& sat_solver = _tr_sat_solver;
    return FormulaInductiveUtils::concrete_transition_to_abs(to_close_nodes, abs_witness, *sat_solver);
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
                                              const ConstAbsStateSet &dsts_abs)
{
    AbstractState& src_abs = find_abs(src_node.get_concrete_state());

    z3::context& ctx = src_abs.get_formula().get_ctx();

    std::unique_ptr<ISatSolver> solver = ISatSolver::s_solvers.at(OmgConfig::get<std::string>("Sat Solver"))(ctx); // TODO
    RefinementResult refinement_res = _abs_structure->refine_exists_successor(src_node.get_concrete_state(), src_abs, dsts_abs, true, *solver);

    update_classifier(refinement_res, src_abs);
    find_abs(src_node); // redundant?
}

void OmgModelChecker::update_classifier(RefinementResult& refine_result, AbstractState& abs_src_witness) {
    if (!refine_result.is_split) return;

    assert(refine_result.split_query->get_raw_formula().num_args() > 0);

    _abs_classifier->split(abs_src_witness, *refine_result.split_query, *refine_result.astate_generalized, *refine_result.astate_remainder);

    refine_result.astate_generalized->set_cl_node(&abs_src_witness.get_cl_node()->get_successor(true));
    refine_result.astate_remainder->set_cl_node(&abs_src_witness.get_cl_node()->get_successor(false));
}

void OmgModelChecker::refine_no_successor(UnwindingTree &to_close_node, AbstractState &abs_src_witness,
                                          AbstractState &abs_dst)
{
    AVY_MEASURE_FN;

    /*
     * One might have thought that we can use here EX+ refinement with the state that we found that does have a transition to
     * absssss_dst in order to conduct the split, instead of this EX- refinement that we conduct.
     * However, this is not ture. he reason is that we want to split AWAY the part of abs_src_witness that includes the reacehable
     * node in the unwinding tree, which is not necessarily done in EX+.
     */
    z3::context& ctx = abs_src_witness.get_formula().get_ctx();
    std::unique_ptr<ISatSolver> solver = ISatSolver::s_solvers.at(OmgConfig::get<std::string>("Sat Solver"))(ctx); // TODO

    RefinementResult refine_res = _abs_structure->refine_no_successor(to_close_node, abs_src_witness, {&abs_dst}, false, *solver);
    update_classifier(refine_res, abs_src_witness);
    find_abs(to_close_node); // redundant?
}

void OmgModelChecker::refine_all_successors(UnwindingTree& to_close_node, const std::set<const UnwindingTree*>& dsts_nodes)
{
    ConstAbsStateSet dsts_abs;
    for (const UnwindingTree* dst_node : dsts_nodes) dsts_abs.insert(&find_abs(dst_node->get_concrete_state()));

    AbstractState& abs_src_witness = find_abs(to_close_node);

    z3::context& ctx = abs_src_witness.get_formula().get_ctx();
    std::unique_ptr<ISatSolver> solver = ISatSolver::s_solvers.at(OmgConfig::get<std::string>("Sat Solver"))(ctx); // TODO

    RefinementResult refine_res = _abs_structure->refine_all_successors(to_close_node, abs_src_witness, dsts_abs, true, *solver);
    update_classifier(refine_res, abs_src_witness);
    find_abs(to_close_node); // redundant?
}

void
OmgModelChecker::refine_exists_successor(UnwindingTree &src_node, const std::set<const ConcreteState *> &dsts_abs) {
    ConstAbsStateSet dsts_astates;
    for (const auto& it : dsts_abs)dsts_astates.emplace(&find_abs(*it));
    refine_exists_successor(src_node, dsts_astates);
}

bool OmgModelChecker::handle_equiv(Goal &goal) {
    Goal first_subgoal(goal.get_node(), *goal.get_spec().get_operands()[0], goal.get_properties());
    bool first_res = recur_ctl(first_subgoal);
    Goal second_subgoal(goal.get_node(), *goal.get_spec().get_operands()[1], goal.get_properties());
    bool second_res = recur_ctl(second_subgoal);
    return first_res == second_res;}


InductiveCandidate::InductiveCandidate(AbstractState *_abs_state, std::unordered_set<UnwindingTree *> _nodes)
    : abs_state(_abs_state), nodes(std::move(_nodes))
{
    avg_depth = ((double) std::accumulate(_nodes.begin(), _nodes.end(), 0U,
            [] (size_t partial_sum, UnwindingTree* node) {  return node->get_depth() + partial_sum; } ) ) / _nodes.size();
}
