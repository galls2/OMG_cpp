#include <utility>

//
// Created by galls2 on 04/10/19.
//

#include <queue>
#include <unordered_set>
#include <utils/z3_utils.h>
#include "omg_model_checker.h"


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

        };

bool OmgModelChecker::handle_and(Goal &goal) {
        Goal first_subgoal(goal.get_node(), *goal.get_spec().get_operands()[0], goal.get_properties());
        bool first_res = recur_ctl(first_subgoal);
        if (!first_res) return false;
        Goal second_subgoal(goal.get_node(), *goal.get_spec().get_operands()[1], goal.get_properties());
        bool second_res = recur_ctl(second_subgoal);
        return second_res;
}

bool OmgModelChecker::handle_or(Goal &goal) {
        Goal first_subgoal(goal.get_node(), *goal.get_spec().get_operands()[0], goal.get_properties());
        bool first_res = recur_ctl(first_subgoal);
        if (first_res) return true;
        Goal second_subgoal(goal.get_node(), *goal.get_spec().get_operands()[1], goal.get_properties());
        bool second_res = recur_ctl(second_subgoal);
        return second_res;
}

bool OmgModelChecker::handle_not(Goal &goal) {
        Goal subgoal(goal.get_node(), *goal.get_spec().get_operands()[0], goal.get_properties());
        bool result = recur_ctl(subgoal);
        return !result;
}

bool OmgModelChecker::handle_xor(Goal &goal) {
        Goal first_subgoal(goal.get_node(), *goal.get_spec().get_operands()[0], goal.get_properties());
        bool first_res = recur_ctl(first_subgoal);
        Goal second_subgoal(goal.get_node(), *goal.get_spec().get_operands()[1], goal.get_properties());
        bool second_res = recur_ctl(second_subgoal);
        return first_res ^ second_res;
}

bool OmgModelChecker::handle_arrow(Goal &goal) {
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

    while (!to_visit.empty())
    {
        UnwindingTree& node_to_explore = to_visit.top();
        to_visit.pop();
        node_to_explore.set_urgent(false);

        // CHECK - we will delete this later. This checks for twice for the same concrete state
        assert(!std::any_of(visited.begin(), visited.end(), [&](const ConcreteState* const& visitedee)
        {
                return node_to_explore.get_concrete_state().to_bitvec() == visitedee->to_bitvec();
        }));

        visited.emplace(&node_to_explore.get_concrete_state());

        (void) find_abs(node_to_explore);
        node_to_explore.set_developed(goal);

        const CtlFormula& q = *goal.get_spec().get_operands()[0];
        Goal subgoal_q(goal.get_node(), q, goal.get_properties());
        bool res_q = recur_ctl(subgoal_q);
        if (!res_q) // nte |/= q
        {
            /*
             * This is the case of a refuting path!
             */
            handle_proving_trace(goal.get_properties().at("strengthen"), goal, node_to_explore);
            return false;
        }

        const CtlFormula& p = *goal.get_spec().get_operands()[1];
        Goal subgoal_p(goal.get_node(), p, goal.get_properties());
        bool res_p = recur_ctl(subgoal_p);
        if (res_p) {
                AbstractState &astate = find_abs(node_to_explore);
                astate.add_label(true, p);
        } else {
                const std::vector<std::unique_ptr<UnwindingTree>> &successors = node_to_explore.unwind_further();
                for (const std::unique_ptr<UnwindingTree> &succ : successors) {
                        if (std::all_of(visited.begin(), visited.end(), [&succ](const ConcreteState *const &visitedee)
                        {
                            return !(visitedee == &(succ->get_concrete_state()) ||
                                     (*visitedee == succ->get_concrete_state()));
                        })) {
                                to_visit.emplace(std::ref(*succ));
                        }
                }
        }

        bool inductive_res = check_inductive_av(goal, to_visit);
        if (inductive_res) {
                label_subtree(goal.get_node(), goal.get_spec(), true);
                return true;
        }
}
        if (goal.get_properties().at("strengthen"))
        {
                strengthen_subtree(goal, [goal](const UnwindingTree& n) { return n.is_developed(goal); });
                label_subtree(goal.get_node(), goal.get_spec(), true);
                return true;
        }
        else {
                return true;
        }
}

void OmgModelChecker::strengthen_subtree(Goal& goal, const std::function<bool(const UnwindingTree&)>& stop_condition)
{
        throw OmgMcException("Not implemented!");
    // use unwinding tree map method


}


AbstractState next_to_av_close(const std::map<std::reference_wrapper<AbstractState>, std::unordered_set<const UnwindingTree*>>& abs_states_lead)
{
    double max_avg = 0.0;
    AbstractState* max_abs = nullptr;
    for (auto& it : abs_states_lead) {
        double curr_avg = 0.0;
        for (const UnwindingTree* const& node : it.second)
            curr_avg += node->get_depth();
        curr_avg /= it.second.size();

        if (max_avg < curr_avg) { max_avg = curr_avg; max_abs = &it.first.get(); }
    }
    assert(max_abs != nullptr);
    return *max_abs;
}

bool OmgModelChecker::check_inductive_av(Goal& goal, NodePriorityQueue& to_visit)
{
    CandidateSet candidates = compute_candidate_set(goal, _opt_brother_unif);

    std::set<std::reference_wrapper<AbstractState>> abs_states;
    for (const auto& it : candidates) abs_states.emplace(*it.first);

    auto comp_ind_cands = [](const InductiveCandidate& a, const InductiveCandidate& b) { return a.avg_depth < b.avg_depth; };
    std::priority_queue<InductiveCandidate, std::vector<InductiveCandidate>, decltype(comp_ind_cands)> abs_states_lead(comp_ind_cands);
    for (const auto &it: candidates) {
        if (it.first->is_neg_labeled(*goal.get_spec().get_operands()[1]))
        {
            abs_states_lead.emplace(it.first, it.second);
        }
    }

    while (!abs_states_lead.empty())
    {
        InductiveCandidate ind_candidate = abs_states_lead.top();
        AbstractState* abs_lead = ind_candidate.abs_state;

        EEClosureResult res = _abs_structure->is_EE_closure(*abs_lead, abs_states);
        if (res.is_closed) { abs_states_lead.pop(); }
        else
            {
            assert(res.src);
            assert(res.dst);

            ConcreteState src = *(res.src), dst = *(res.dst);
            AbstractState& abs_dst = find_abs(dst);

            ConcretizationResult concretization_result = is_concrete_violation(ind_candidate.nodes, abs_dst);
   //         AbstractState&
     //       ConcretizationResult concretization_result = is_concrete_violation(ind_candidate.nodes, )
            if (concretization_result.dst_cstate)
            {
                // More Unwinding
                const ConcreteState& dst_cstate = *concretization_result.dst_cstate;
                UnwindingTree* const to_close_node = concretization_result.src_node;

                UnwindingTree& node_to_set =
                        to_close_node->exist_successors() ?
                            **std::find_if(to_close_node->get_successors().begin(), to_close_node->get_successors().end(),
                                [&dst_cstate](const std::unique_ptr<UnwindingTree>& successor) {return successor->get_concrete_state() == dst_cstate;})
                                : *to_close_node;

                node_to_set.set_urgent(true);


            //    UnwindingTree* node_to_set = to_close_node.
            }
            else
            {
                // (EX-) refinement

            }

            return false;
        }
    }
}

CandidateSet OmgModelChecker::compute_candidate_set(Goal& goal, bool brother_unif)
{
    CandidateSet cands;
    UnwindingTree& root = goal.get_node();
    auto inserter = [&cands] (UnwindingTree& node)
    {
        auto abs = node.get_abs();
        assert(abs);

        AbstractState* p_abs = &(abs->get());
        std::unordered_set<UnwindingTree*> node_set;
        node_set.insert(&node);
        if (cands.find(p_abs) == cands.end())
        {

            cands.emplace(p_abs, node_set);
        } else
            cands[p_abs].emplace(&node);
    };
    root.map(inserter, [&goal](const UnwindingTree& node) { return node.is_developed(goal);  });

    if (brother_unif)
        return brother_unification(cands, *(goal.get_spec().get_operands()[1]));
    else return cands;
}

void unify_same_level(CandidateSet& src, const CtlFormula& agree_upon, CandidateSet& unchanged, CandidateSet& next_level) {
    std::map<const AbstractClassificationNode *, std::pair<AbstractState*, std::vector<std::unordered_set<UnwindingTree*>>>> parents_mapping;

    for (const std::pair<AbstractState* const, std::unordered_set<UnwindingTree*>>& it : src) {
        const AbstractClassificationNode* parent = it.first->get_cl_node()->get_parent();
        assert(parent != nullptr);
//        if (parents_mapping.find(parent) == parents_mapping.end())
//            parents_mapping[parent] = std::pair<AbstractState*, std::vector<std::unordered_set<UnwindingTree*>>>();
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
        if (levels.find(depth) == levels.end()) levels[depth] = {it};
        else levels[depth].emplace(it);
    }

    CandidateSet reduced;
    for (size_t depth = max_depth; depth > 0; --depth)
    {
        if (levels.find(depth) == levels.end() || levels[depth].empty()) continue;

        CandidateSet unchanged, next_level;
        unify_same_level(levels[depth], agree_upon, unchanged, next_level);
    }

    if (levels.find(0) != levels.end()) reduced.insert(levels[0].begin(), levels[0].end());

    return reduced;
}


bool OmgModelChecker::handle_er(Goal &goal)
{
        throw OmgMcException("Not implemented!");
}

bool OmgModelChecker::handle_ex(Goal &goal)
{
        throw OmgMcException("Not implemented!");
}

OmgModelChecker::OmgModelChecker(const KripkeStructure &kripke, const OmgConfiguration &config)
: _kripke(kripke),
        _opt_trivial_splits(config.get<bool>("Trivial Split Elimination")),
        _opt_brother_unif(config.get<bool>("Brother Unification")),
        _sat_solver(config.get<std::string>("Sat Solver"))
{
        initialize_abstraction();
}

void OmgModelChecker::initialize_abstraction()
{
        _abs_structure = std::make_unique<AbstractStructure>(_kripke, this);
        _abs_classifier = std::make_unique<AbstractionClassifier>(_kripke);
}

bool OmgModelChecker::model_checking(ConcreteState &cstate, const CtlFormula &specification) {

        // In the future - unwinding tree cache is to be used here
        std::unique_ptr<UnwindingTree> root = std::make_unique<UnwindingTree>(_kripke, cstate, nullptr);

        root->reset_developed_in_tree();

        Goal goal(*root, specification, {{"strengthen", true}});
        bool result = recur_ctl(goal);
        return result;
}

bool OmgModelChecker::recur_ctl(Goal &g) {
        AbstractState& astate = find_abs(g.get_node());
        const CtlFormula& spec = g.get_spec();

        if (astate.is_pos_labeled(spec)) return true;
        if (astate.is_neg_labeled(spec)) return false;

        if (spec.is_boolean())
        {
                return spec.get_boolean_value();
        }

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

AbstractState &OmgModelChecker::find_abs(const ConcreteState &cstate) {
    if (!_abs_classifier->exists_classification(cstate))
    {
        AbstractState &astate = _abs_structure->create_abs_state(cstate);
        _abs_classifier->add_classification_tree(cstate, astate);
        return astate;
    }
    else
    {
        AbstractState& abs = _abs_classifier->classify(cstate);
        return abs;
    }
}

void OmgModelChecker::handle_proving_trace(bool is_strengthen, Goal &goal, UnwindingTree &node) {
        if (is_strengthen)
                throw OmgMcException("Not implemented");
}

void OmgModelChecker::label_subtree(UnwindingTree &node, const CtlFormula& spec, bool positivity) {
    node.map([positivity, &spec](UnwindingTree& n) {
        assert(n.get_abs());
        n.get_abs()->get().add_label(positivity, spec);
        }, [](const UnwindingTree&) { return true; });
}

ConcretizationResult
OmgModelChecker::is_concrete_violation(const std::unordered_set<UnwindingTree *> &to_close_nodes,
                                       AbstractState &abs_witness) {
    return FormulaInductiveUtils::concrete_transition_to_abs(to_close_nodes, abs_witness, _sat_solver);
}


UnwindingTree &Goal::get_node() {
        return _node;
}

const CtlFormula &Goal::get_spec() const {
        return _spec;
}

const std::map<std::string, bool> &Goal::get_properties() const {
        return _properties;
}

Goal::Goal(UnwindingTree &node, const CtlFormula &spec,
           std::map<std::string, bool> properties)
 : _node(node), _spec(spec), _properties(std::move(properties))
{}
