#pragma once
//
// Created by galls2 on 12/10/19.
//

#include <structures/kripke_structure.h>

class AbstractState {
//public:
//    AbstractState(const KripkeStructure& kripke, CtlFormula::PropertySet pos_labels, PropertySet atomic_labels, PropFormula sym_rep);
//
//private:
//    const KripkeStructure& _kripke;
//    PropertySet _pos_labels;
//    PropertySet _neg_labels;
//    PropertySet _atomic_labels;
//    // classssssssificatin node
//    PropFormula _sym_rep;
#ifndef DEBUG
    std::string _debug_name;
#endif
};

