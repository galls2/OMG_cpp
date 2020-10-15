//
// Created by galls2 on 20.9.2020.
//

#include "concrete_set.h"


bool ConcreteSet::operator==(const ConcreteSet &other) const {
   // return z3::eq(other._conjunct, _conjunct);
   throw 5;
}

bool ConcreteSet::operator!=(const ConcreteSet &other) const {
    return !(*this == other);
}


#ifdef DEBUG

std::vector<bool> ConcreteSet::to_bitvec() const
{
   throw 9;

}

std::string ConcreteSet::to_bitvec_str() const {
 throw 9;
}

#endif