#pragma once
//
// Created by galls2 on 12/10/19.
//

#include <structures/kripke_structure.h>


class AbstractClassificationNode;

class AbstractState {
public:
    AbstractState(const KripkeStructure& kripke, std::unique_ptr<CtlFormula::PropertySet> pos_labels,
                  const CtlFormula::PropertySet& atomic_labels, PropFormula sym_rep);
    bool operator<(const AbstractState& other) const;
private:
    const KripkeStructure& _kripke;
    std::unique_ptr<CtlFormula::PropertySet> _pos_labels;
    std::unique_ptr<CtlFormula::PropertySet> _neg_labels;
    const CtlFormula::PropertySet& _atomic_labels;
    AbstractClassificationNode* _cl_node;
    PropFormula _sym_rep;
#ifndef DEBUG
    std::string _debug_name;
#endif
};

