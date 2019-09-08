//
// Created by galls2 on 30/08/19.
//
#include <iostream>
#include "z3++.h"
#include "code/parsers/aig_parser.h"
using namespace z3;

void test_z3() {
    std::cout << "Hello, OMG in c++!" << std::endl;
    context c;

    expr x = c.bool_const("x");
    expr y = c.bool_const("y");
    expr conjecture = (!(x && y)) == (!x || !y);

    solver s(c);
    // adding the negation of the conjecture as a constraint.
    s.add(!conjecture);
    std::cout << s << "\n";
    std::cout << s.to_smt2() << "\n";
    switch (s.check()) {
        case unsat:   std::cout << "de-Morgan is valid\n"; break;
        case sat:     std::cout << "de-Morgan is not valid\n"; break;
        case unknown: std::cout << "unknown\n"; break;
    }
}
int main()
{
    AigParser p(R"(/home/galls2/Desktop/af_ag.aig)");


}