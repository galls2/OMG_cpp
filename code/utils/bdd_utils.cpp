//
// Created by galls2 on 29.7.2020.
//

#include "bdd_utils.h"

BDD&& BddUtils::expr_to_bdd(Cudd& mgr, const z3::expr &expr,  const std::map<z3::expr, size_t, Z3ExprComp>& var_mapping)
{
    z3::context& ctx = expr.ctx();

    if (z3::eq(expr, ctx.bool_val(true))) return std::move(mgr.bddOne());
    if (z3::eq(expr, ctx.bool_val(false))) return std::move(mgr.bddZero());

    if (expr.is_const())
    {
        assert(expr.num_args() == 0);
        assert(var_mapping.find(expr) != var_mapping.end());
        size_t var_num = var_mapping.at(expr);
        BDD var_bdd = mgr.bddVar(var_num);
        return std::move(var_bdd);
    }

    if (expr.is_not())
    {
        assert(expr.num_args() == 1);
        BDD inner = expr_to_bdd(mgr, expr.arg(0), var_mapping);
        return std::move(!inner);
    }

    if (expr.is_and())
    {
        BDD and_result_bdd = mgr.bddOne();
        for (size_t i = 0; i < expr.num_args(); ++i)
        {
            BDD and_part_bdd = expr_to_bdd(mgr, expr.arg(i), var_mapping);
            and_result_bdd &= and_part_bdd;
        }
        return std::move(and_result_bdd);
    }

    if (expr.is_or())
    {
        BDD or_result_bdd = mgr.bddZero();
        for (size_t i = 0; i < expr.num_args(); ++i)
        {
            BDD or_part_bdd = expr_to_bdd(mgr, expr.arg(i), var_mapping);
            or_result_bdd |= or_part_bdd;
        }
        return std::move(or_result_bdd);
    }

    std::cout << expr.to_string() << std::endl;
    assert(false);
    throw BddException("Illegal operator in expression");
}

void BddUtils::bdd_to_dot(Cudd &mgr, const BDD &bdd, const std::string& write_path, size_t num_vars , char** names)
{
    FILE* outfile;
    outfile = fopen(write_path.data(), "w");
    DdNode **ddnodearray = (DdNode**)malloc(sizeof(DdNode*)); // initialize the function array
    ddnodearray[0] = bdd.getNode();
//    Cudd_DumpDot(mgr.getManager(), num_vars, ddnodearray, names, names, outfile);
    Cudd_DumpDot(mgr.getManager(), num_vars, ddnodearray, names, NULL, outfile);
    free(ddnodearray);
    fclose(outfile);
}

std::string BddUtils::bdd_to_string(DdNode *root, Cudd &mgr, size_t init_num_tabs) {
   // std::string
}




std::vector<BddUtils::CubeRep> BddUtils::all_sat(Cudd &mgr, const BDD &bdd) {
    std::map<DdNode *, std::vector<CubeRep>> node_cube_reps;

    bool is_initially_complemented = Cudd_IsComplement(bdd.getNode());
    all_sat(mgr, bdd, node_cube_reps, is_initially_complemented);
    return node_cube_reps[bdd.getRegularNode()];
}

void
BddUtils::all_sat(Cudd &mgr, const BDD &bdd, std::map<DdNode *, std::vector<CubeRep>> & node_cube_reps, bool is_negate)
{
    if ((bdd.IsOne() && !is_negate) || (bdd.IsZero() && is_negate))
    {
        std::cout << "BDD leaf" << std::endl;
        node_cube_reps[bdd.getRegularNode()] = {{}};
        return;
    }
    else if (((bdd.IsOne() && is_negate) || (bdd.IsZero() && !is_negate)))
    {
//        node_cube_reps[bdd.getRegularNode()] = {};
        return;

    }
    // eliminate ret value and
    // make_______cup_repppp an array
    // correctify
   std::cout << "-------NOT BDD leaf" << std::endl;

    DdNode* current_node = bdd.getRegularNode();
    size_t idx = Cudd_NodeReadIndex(current_node);
    std::cout << "INDEX: "<<idx << std::endl;


    if (node_cube_reps.find(current_node) != node_cube_reps.end())
    {
        std::cout << "YASA" << std::endl;
        return; // node_cube_reps[current_node];
    }

    std::vector<BddUtils::CubeRep> to_return;

    DdNode* then_node = Cudd_T(current_node);
    bool is_then_node_complemented = Cudd_IsComplement(then_node);

    then_node = Cudd_Regular(then_node);
    BDD then_bdd(mgr, then_node);
    std::cout<<"GOIND TO THE LEFT OF " << idx<<std::endl;
    all_sat(mgr, then_bdd, node_cube_reps, is_negate ^ is_then_node_complemented);

    for (auto& it : node_cube_reps[then_node])
    {
        // move?
        CubeRep cube_rep = it;
        cube_rep.insert(cube_rep.begin(), idx);

        std::for_each(cube_rep.begin(), cube_rep.end(), [](ssize_t x) { std::cout << x << " ";});
        to_return.emplace_back(std::move(cube_rep));
        std::cout << std::endl;
    }

    DdNode* else_node = Cudd_E(current_node);
    bool is_else_node_complemented = Cudd_IsComplement(else_node);

    else_node = Cudd_Regular(else_node);;
    BDD else_bdd(mgr, else_node);
    std::cout<<"GOIND TO THE RIGHT OF " << idx<<std::endl;

    all_sat(mgr, else_bdd, node_cube_reps, is_negate ^ is_else_node_complemented);
    for (auto& it : node_cube_reps[else_node])
    {
        // move?
        CubeRep cube_rep = it;
        cube_rep.insert(cube_rep.begin(), -1*idx);
        
        std::for_each(cube_rep.begin(), cube_rep.end(), [](ssize_t x) { std::cout << x << " ";});
        to_return.emplace_back(std::move(cube_rep));
        std::cout << std::endl;
    }
    std::cout<<"DONE WITH " << idx<<std::endl;

    node_cube_reps[current_node] = to_return;
}
