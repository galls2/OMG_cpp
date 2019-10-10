//
// Created by galls2 on 29/09/19.
//

#include <utils/z3_utils.h>
#include <formulas/sat_solver.h>
#include "kripke_structure.h"



std::vector<ConcreteState> KripkeStructure::get_initial_states() const
{
    //CHANGE
    z3::context& ctx = _transitions.get_formula().ctx();
    Z3SatSolver solver(ctx);
    const auto& ps_vars = _transitions.get_vars_by_tag("ps");
    std::map<std::string, z3::expr_vector> mp = {{"ps", ps_vars}};
    PropFormula p(_init_formula, mp);
    std::vector<SatSolverResult> results = solver.all_sat(p, expr_vector_to_vector(ps_vars), true);
    std::vector<ConcreteState> init_states;
    for (const auto& result : results)
    {
        init_states.emplace_back(*this, result.to_conjunt(ctx));
    }
    return init_states;
}
