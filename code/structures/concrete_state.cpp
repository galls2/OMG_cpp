//
// Created by galls2 on 04/10/19.
//

#include "concrete_state.h"

std::vector<ConcreteState> ConcreteState::get_successors() {
    if (!_successors) compute_successors();
    return _successors.value();
}

void ConcreteState::compute_successors() {
    const z3::expr& tr = _kripke.get_tr().get_formula();


}
