#pragma once
//
// Created by galls2 on 04/10/19.
//


#include <structures/kripke_structure.h>
#include <abstraction/abstract_structure.h>
#include <abstraction/abstraction_classifier.h>
#include <structures/unwinding_tree.h>
#include <configuration/omg_config.h>

DECLARE_OMG_EXCEPTION(OmgMcException)

class UnwindingTree;

struct Goal
{
    Goal(const UnwindingTree& node, const CtlFormula& spec, const std::map<std::string, bool>& properties);
    const UnwindingTree &get_node() const;
    const CtlFormula &get_spec() const;
    const std::map<std::string, bool> &get_properties() const;
private:
    const UnwindingTree& _node;
    const CtlFormula& _spec;
    const std::map<std::string, bool> _properties;
};

class OmgModelChecker {
public:


    typedef bool (OmgModelChecker::*handler_t)(const Goal& goal);
    bool model_checking(const ConcreteState& cstate, const CtlFormula& specification);

    OmgModelChecker(const KripkeStructure& kripke, const OmgConfiguration& config);

private:
    const KripkeStructure& _kripke;
    std::unique_ptr<AbstractStructure> _abs_structure;
    std::unique_ptr<AbstractionClassifier> _abs_classifier;
   // std::map<std::unique_ptr<UnwindingTree>> _unwinding_trees;


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
    bool handle_ar(const Goal& goal);
    bool handle_er(const Goal& goal);
    bool handle_ex(const Goal& goal);

    void initialize_abstraction();

    AbstractState& find_abs(const UnwindingTree& node);
    static const std::map<std::string, handler_t> _handlers;
};

