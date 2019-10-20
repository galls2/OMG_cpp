#pragma once
#include <utility>

//
// Created by galls2 on 04/10/19.
//

#include <experimental/optional>
#include <vector>
#include <structures/kripke_structure.h>
#include <temporal/ctl_formula.h>

class KripkeStructure;


class ConcreteState {
public:
    ConcreteState(const KripkeStructure& kripke, z3::expr conjunct);

    std::vector<ConcreteState> get_successors();
    bool is_labeled_with(const std::string& ap) const;
    void aps_by_sat(CtlFormula::PropertySet& pos, CtlFormula::PropertySet& neg) const;
    std::set<std::string> string_sat_aps() const;
    PropFormula get_bis0_formula() const;
#ifndef DEBUG
    std::vector<bool> to_bitvec() const;
#endif
    friend std::ostream& operator<< (std::ostream& stream, const ConcreteState& concrete_state);

private:
    const KripkeStructure& _kripke;
    const z3::expr _conjunct;
    std::experimental::optional<std::vector<ConcreteState>> _successors;


    void compute_successors();
};

