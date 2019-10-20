#pragma once
//
// Created by galls2 on 12/10/19.
//

#include <structures/kripke_structure.h>


class AbstractClassificationNode;

class AbstractState {
public:
    AbstractState(const KripkeStructure& kripke, CtlFormula::PropertySet pos_labels, CtlFormula::PropertySet atomic_labels, PropFormula sym_rep);
    bool operator<(const AbstractState& other) const;
    bool is_pos_labeled(const CtlFormula& spec) const;
    bool is_neg_labeled(const CtlFormula& spec) const;
    void add_label(bool positivity, const CtlFormula& spec);
private:
    const KripkeStructure& _kripke;
    CtlFormula::PropertySet _pos_labels;
    CtlFormula::PropertySet _neg_labels;
    CtlFormula::PropertySet _atomic_labels;
    AbstractClassificationNode* _cl_node;
    PropFormula _sym_rep;
#ifndef DEBUG
    std::string _debug_name;
#endif
};
