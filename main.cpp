//
// Created by galls2 on 30/08/19.
//
#include <iostream>
#include "z3++.h"
#include <parsers/aig_parser.h>
#include <parsers/ctl_parser.h>
#include <parsers/lexer.h>
#include <parsers/ctl_parser_data.h>
#include <parsers/ctl_file_parser.h>
#include <utils/aiger-1.9.9/aig_to_aag.h>
using namespace z3;

void test_z3() {
    std::cout << "Hello, OMG in C++!" << std::endl;
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

void test_sub() {
    z3::context c;

    z3::expr x = c.bool_const("x");
    z3::expr y = c.bool_const("y");
    z3:: expr f = x && y;
    Z3_ast from[]= {x};
    Z3_ast to[] = {y};

//    z3::expr new_f(c);
//    new_f = z3::to_expr(c, Z3_substitute(c, f, 1, from, to));
//    std::cout << f << std::endl;
//    std::cout << new_f << std::endl;

    z3::solver solver1(c);
    solver1.add(f);
    std::cout << solver1.check() << std::endl;
    std::cout << solver1.get_model() << std::endl;
    z3::model m = solver1.get_model();
    std::cout << "VAMV AMVAM:: " << z3::eq(m.eval(x), c.bool_val(true)) << std::endl;
}


void test_parser()
{
    Lexer lexer;
    //   auto res = lexer.lex("AG ( p -> q)");

    auto res = lexer.lex("AG(req1<0> & ack0 -> AX ack1)");
    for (const auto &r : res)
    {
        std::cout << r << ".";
    }
    std::cout << std::endl;


    LR1CtlParser parser(CtlParserData::grammar_ctl, ActionTable(CtlParserData::action_table_ctl_parser), GotoTable(CtlParserData::goto_table_ctl_parser));
    std::unique_ptr<CtlFormula> formula = parser.parse(res);
    std::cout << formula->to_string() <<  std::endl;
}

void test_ctl_file_parser()
{
    CtlFileParser ctl_file_parser;
    std::vector<FormulaChunk> formula_chunks;
    ctl_file_parser.parse_ctl_file("/home/galls2/Desktop/spm.ctl", formula_chunks);
    for (const auto& chunk : formula_chunks)
    {
        std::cout << chunk.get_expected_result() << std::endl;
        for (const auto& formula : chunk.get_formulas())
            std::cout << formula->to_string() << std::endl;
    }
}

int main()
{
    AigParser p(R"(/home/galls2/Desktop/af_ag.aig)");
    auto val = p.to_kripke({});
    auto init = val.get_first_initial_state();
    std::cout << "Init: "<<init << std::endl;
    auto succ = init.get_successors();
    std:: cout << "Successors: ";
    for (const auto &s : succ)
        std::cout << s << std::endl;


//    std::cout << val.get_tr().get_formula().to_string() << std::endl;
 //   std::cout << "UPUU";
    test_sub();
}