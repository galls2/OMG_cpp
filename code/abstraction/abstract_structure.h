//
// Created by galls2 on 04/10/19.
//

#ifndef OMG_CPP_ABSTRACT_STRUCTURE_H
#define OMG_CPP_ABSTRACT_STRUCTURE_H


#include <structures/kripke_structure.h>

class AbstractStructure {
public:
    explicit AbstractStructure(const KripkeStructure& kripke);
private:
    const KripkeStructure& _kripke;

    //NE MAY , E MAY OVER, , NE MAY OVER, E MUST
};


#endif //OMG_CPP_ABSTRACT_STRUCTURE_H
