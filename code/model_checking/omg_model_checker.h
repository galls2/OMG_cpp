//
// Created by galls2 on 04/10/19.
//

#ifndef OMG_CPP_OMG_MODEL_CHECKER_H
#define OMG_CPP_OMG_MODEL_CHECKER_H


#include <structures/kripke_structure.h>
#include <abstraction/abstract_structure.h>
#include <abstraction/abstraction_classifier.h>
#include <structures/unwinding_tree.h>
#include <configuration/omg_config.h>

class OmgModelChecker {
public:
    struct Goal
    {
        const UnwindingTree &get_node() const;
        const CtlFormula &get_spec() const;
        const std::set<CtlFormula *> &get_spec_components() const;
        const std::map<std::string, bool> &get_properties() const;

        const UnwindingTree& _node;
        const CtlFormula& _spec;
        const std::set<CtlFormula*> _spec_components;
        const std::map<std::string, bool> _properties;
    };

    typedef bool (OmgModelChecker::*handler_t)(const Goal& goal);

    OmgModelChecker(const KripkeStructure& kripke, const OmgConfiguration& config);

private:
    const KripkeStructure& _kripke;
    std::unique_ptr<AbstractStructure> _abs_structure;
    std::unique_ptr<AbstractionClassifier> _abs_classifier;
    std::set<std::unique_ptr<UnwindingTree>> _unwinding_trees;


    /*
     * Configurable Properties
     */
    const bool _opt_trivial_splits; // Is the Trivial Split Elimination optimization activated
    const bool _opt_brother_unif; // Is the Trivial Split Elimination optimization activated

    /*
     * Model Checking
     */
    bool recur_ctl(const Goal& g);

    /*
     * Handlers
     */
    bool handle_and(const Goal& goal);
    bool handle_or(const Goal& goal);
    bool handle_not(const Goal& goal);
    bool handle_xor(const Goal& goal);
    bool handle_arrow(const Goal& goal);
    bool handle_av(const Goal& goal);
    bool handle_ev(const Goal& goal);
    bool handle_ex(const Goal& goal);

    bool handle_ap(const Goal& goal);

    void initialize_abstraction();

    static const std::map<std::string, handler_t> _handlers;
};


#endif //OMG_CPP_OMG_MODEL_CHECKER_H
