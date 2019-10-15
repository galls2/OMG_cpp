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

bool OmgModelChecker::handle_and(const OmgModelChecker::Goal &goal) {
        return false;
}

bool OmgModelChecker::handle_or(const OmgModelChecker::Goal &goal) {
        return false;
}

bool OmgModelChecker::handle_not(const OmgModelChecker::Goal &goal) {
        return false;
}

bool OmgModelChecker::handle_xor(const OmgModelChecker::Goal &goal) {
        return false;
}

bool OmgModelChecker::handle_arrow(const OmgModelChecker::Goal &goal) {
        return false;
}

bool OmgModelChecker::handle_av(const OmgModelChecker::Goal &goal) {
        return false;
}

bool OmgModelChecker::handle_ev(const OmgModelChecker::Goal &goal) {
        return false;
}

bool OmgModelChecker::handle_ex(const OmgModelChecker::Goal &goal) {
        return false;
}

bool OmgModelChecker::handle_ap(const OmgModelChecker::Goal &goal) {
        return false;
}

OmgModelChecker::OmgModelChecker(const KripkeStructure &kripke, const OmgConfiguration &config)
: _kripke(kripke),
        _opt_trivial_splits(config.get_bool_value("Trivial Split Elimination")),
        _opt_brother_unif(config.get_bool_value("Brother Unification"))
{
        initialize_abstraction();
}

void OmgModelChecker::initialize_abstraction()
{
        _abs_structure = std::make_unique<AbstractStructure>(_kripke);
        _abs_classifier = std::make_unique<AbstractionClassifier>(_kripke);
}


const UnwindingTree &OmgModelChecker::Goal::get_node() const {
        return _node;
}

const CtlFormula &OmgModelChecker::Goal::get_spec() const {
        return _spec;
}

const std::set<CtlFormula *> &OmgModelChecker::Goal::get_spec_components() const {
        return _spec_components;
}

const std::map<std::string, bool> &OmgModelChecker::Goal::get_properties() const {
        return _properties;
}
