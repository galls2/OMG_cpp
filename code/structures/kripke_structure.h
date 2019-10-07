#pragma once

#include <set>
#include <utility>
#include <z3++.h>
#include <formulas/prop_formula.h>
#include <structures/concrete_state.h>
#include <utils/cartesian_product_generator.h>
class ConcreteState;

class KripkeStructure {
public:
    KripkeStructure(PropFormula tr, std::set<std::string> aps, CartesianProductGenerator<z3::expr>& init_gen)
    : _transitions(std::move(tr)), _aps(std::move(aps)), _init_gen(init_gen) {}
    const PropFormula& get_tr() const { return _transitions; }
    ConcreteState get_first_initial_state();
    std::experimental::optional<ConcreteState> get_next_initial_state();
private:
    ConcreteState literals_to_state(const std::vector<z3::expr>& literals) const;

    const PropFormula _transitions;
    const std::set<std::string> _aps;
    CartesianProductGenerator<z3::expr>& _init_gen;


};

