#include <utility>

//
// Created by galls2 on 04/10/19.
//

#include <queue>
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

bool OmgModelChecker::check_inductive_av(Goal& goal, NodePriorityQueue& to_visit)
{
        throw OmgMcException("Not implemented!");
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
        _opt_brother_unif(config.get<bool>("Brother Unification"))
{
        initialize_abstraction();
}

void OmgModelChecker::initialize_abstraction()
{
        _abs_structure = std::make_unique<AbstractStructure>(_kripke);
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
        if (!_abs_classifier->exists_classification(cstate))
        {
                if (node.get_abs())
                {
                        AbstractState &astate = *node.get_abs();
                        if (astate.is_final_classification()) return astate;
                        else {
                                AbstractState &updated_abs = _abs_classifier->update_classification(astate,
                                                                                                   node.get_concrete_state());
                                node.set_abs(updated_abs);
                                return updated_abs;
                        }
                }
                else {
                        AbstractState &astate = _abs_structure->create_abs_state(cstate);
                        _abs_classifier->add_classification_tree(cstate, astate);
                        node.set_abs(astate);
                        return astate;
                }
        }
        else
        {
                AbstractState& abs = _abs_classifier->classify(cstate);
                node.set_abs(abs);
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
