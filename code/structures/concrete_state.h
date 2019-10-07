#pragma once
#include <utility>

//
// Created by galls2 on 04/10/19.
//

#include <experimental/optional>
#include <vector>
#include <structures/kripke_structure.h>
class KripkeStructure;

class ConcreteState {
public:
    ConcreteState(const KripkeStructure& kripke, const z3::expr &conjunct);

    std::vector<ConcreteState> get_successors();
    friend std::ostream& operator<< (std::ostream& stream, const ConcreteState& concrete_state);

private:
    const KripkeStructure& _kripke;
    const z3::expr _conjunct;
    std::experimental::optional<std::vector<ConcreteState>> _successors;


    void compute_successors();
};

