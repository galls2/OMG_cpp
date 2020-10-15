//
// Created by galls2 on 20.9.2020.
//

#ifndef OMG_CPP_CONCRETE_SET_H
#define OMG_CPP_CONCRETE_SET_H


#include <formulas/prop_formula.h>
#include <cuddObj.hh>

class ConcreteSet {
public:
    ConcreteSet(const BDD& bdd) : _bdd(bdd) {}

    bool operator==(const ConcreteSet& other) const;
    bool operator!=(const ConcreteSet& other) const;

#ifdef DEBUG
    std::vector<bool> to_bitvec() const;
    std::string to_bitvec_str() const;
#endif

private:
  //  const PropFormula _prop;
    const BDD _bdd;
};


#endif //OMG_CPP_CONCRETE_SET_H
