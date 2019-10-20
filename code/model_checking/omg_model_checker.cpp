//
// Created by galls2 on 04/10/19.
//

#include "omg_model_checker.h"


const std::map<std::string, OmgModelChecker::handler_t> OmgModelChecker::_handlers =
        {
                {"AND", &OmgModelChecker::handle_and},
                {"OR", &OmgModelChecker::handle_or},
                {"NOT", &OmgModelChecker::handle_not},
                {"XOR", &OmgModelChecker::handle_xor},
                {"ARROW", &OmgModelChecker::handle_arrow},
                {"AV", &OmgModelChecker::handle_av},
                {"EV", &OmgModelChecker::handle_ev},
                {"EX", &OmgModelChecker::handle_ex},

        };

bool OmgModelChecker::handle_and(const Goal &goal) {
        Goal first_subgoal(goal.get_node(), *goal.get_spec().get_operands()[0], goal.get_properties());
        bool first_res = recur_ctl(first_subgoal);
        if (!first_res) return false;
        Goal second_subgoal(goal.get_node(), *goal.get_spec().get_operands()[1], goal.get_properties());
        bool second_res = recur_ctl(second_subgoal);
        return second_res;
}

bool OmgModelChecker::handle_or(const Goal &goal) {
        Goal first_subgoal(goal.get_node(), *goal.get_spec().get_operands()[0], goal.get_properties());
        bool first_res = recur_ctl(first_subgoal);
        if (first_res) return true;
        Goal second_subgoal(goal.get_node(), *goal.get_spec().get_operands()[1], goal.get_properties());
        bool second_res = recur_ctl(second_subgoal);
        return second_res;
}

bool OmgModelChecker::handle_not(const Goal &goal) {
        Goal subgoal(goal.get_node(), *goal.get_spec().get_operands()[0], goal.get_properties());
        bool result = recur_ctl(subgoal);
        return !result;
}

bool OmgModelChecker::handle_xor(const Goal &goal) {
        Goal first_subgoal(goal.get_node(), *goal.get_spec().get_operands()[0], goal.get_properties());
        bool first_res = recur_ctl(first_subgoal);
        Goal second_subgoal(goal.get_node(), *goal.get_spec().get_operands()[1], goal.get_properties());
        bool second_res = recur_ctl(second_subgoal);
        return first_res ^ second_res;
}

bool OmgModelChecker::handle_arrow(const Goal &goal) {
        Goal first_subgoal(goal.get_node(), *goal.get_spec().get_operands()[0], goal.get_properties());
        bool first_res = recur_ctl(first_subgoal);
        if (!first_res) return true;
        Goal second_subgoal(goal.get_node(), *goal.get_spec().get_operands()[1], goal.get_properties());
        bool second_res = recur_ctl(second_subgoal);
        return second_res;
}

bool OmgModelChecker::handle_av(const Goal &goal) {
        throw OmgMcException("Not implemented!");
}

bool OmgModelChecker::handle_ev(const Goal &goal) {
        throw OmgMcException("Not implemented!");
}

bool OmgModelChecker::handle_ex(const Goal &goal) {
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

bool OmgModelChecker::model_checking(const ConcreteState &cstate, const CtlFormula &specification) {

        // In the future - unwinding tree cache is to be used here
        std::unique_ptr<UnwindingTree> root = std::make_unique<UnwindingTree>(_kripke, cstate, nullptr);

        root->reset_developed_in_tree();

        Goal goal(*root, specification, {{"strengthen", true}});
        bool result = recur_ctl(goal);
        return result;
}

bool OmgModelChecker::recur_ctl(const Goal &g) {
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

AbstractState &OmgModelChecker::find_abs(const UnwindingTree &node) {
        const ConcreteState& cstate = node.get_concrete_state();
        if (!_abs_classifier->exists_classification(cstate))
        {
                AbstractState& astate = _abs_structure->create_abs_state(cstate);
                _abs_classifier->add_classification_tree(cstate, astate);
                return astate;
        }
        else
        {
                AbstractState& abs = _abs_classifier->classify(cstate);
                return abs;
        }
}


const UnwindingTree &Goal::get_node() const {
        return _node;
}

const CtlFormula &Goal::get_spec() const {
        return _spec;
}

const std::map<std::string, bool> &Goal::get_properties() const {
        return _properties;
}

Goal::Goal(const UnwindingTree &node, const CtlFormula &spec,
                            const std::map<std::string, bool>& properties)
 : _node(node), _spec(spec), _properties(properties)
{}
