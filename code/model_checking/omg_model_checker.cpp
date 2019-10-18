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
        return false;
}

bool OmgModelChecker::handle_or(const Goal &goal) {
        return false;
}

bool OmgModelChecker::handle_not(const Goal &goal) {
        return false;
}

bool OmgModelChecker::handle_xor(const Goal &goal) {
        return false;
}

bool OmgModelChecker::handle_arrow(const Goal &goal) {
        return false;
}

bool OmgModelChecker::handle_av(const Goal &goal) {
        return false;
}

bool OmgModelChecker::handle_ev(const Goal &goal) {
        return false;
}

bool OmgModelChecker::handle_ex(const Goal &goal) {
        return false;
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

        Goal goal(*root, specification, {});
        bool result = recur_ctl(goal);
        return result;
}

bool OmgModelChecker::recur_ctl(const Goal &g) {
        // Find abs classification

        // Is already true/false - return it
        if (g.get_spec().is_boolean())
        {
                return g.get_spec().get_boolean_value();
        }

        assert(!g.get_spec().get_operands().empty());
        std::string main_connective = g.get_spec().get_data();
        handler_t handler = _handlers.at(main_connective);
        bool result = (this->*handler)(g);
        // If is strengthen

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
