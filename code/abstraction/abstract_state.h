#pragma once
//
// Created by galls2 on 12/10/19.
//

#include <structures/kripke_structure.h>


class AbstractClassificationNode;

class AbstractState {
public:
    AbstractState(const KripkeStructure& kripke, std::set<const CtlFormula*> pos_labels, std::set<const CtlFormula*> atomic_labels, PropFormula sym_rep);
    bool operator<(const AbstractState& other) const;
    bool is_pos_labeled(const CtlFormula& spec) const;
    bool is_neg_labeled(const CtlFormula& spec) const;
    void add_label(bool positivity, const CtlFormula& spec);
private:
    const KripkeStructure& _kripke;
    std::set<const CtlFormula*> _pos_labels;
    std::set<const CtlFormula*> _neg_labels;
    std::set<const CtlFormula*> _atomic_labels;
    AbstractClassificationNode* _cl_node;
    PropFormula _sym_rep;
#ifndef DEBUG
    std::string _debug_name;
#endif
};
