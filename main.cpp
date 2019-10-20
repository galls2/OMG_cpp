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
#include <unordered_set>
#include <model_checking/omg_model_checker.h>

using namespace z3;

void test_parser()
{
    Lexer lexer;
    //   auto res = lexer.lex("AG ( p -> q)");

    auto res = lexer.lex("True");
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

template <typename T>
void print_vec(const std::vector<T>& v, const std::function<std::string(const T&)>& convert)
{
    std::cout << "[";
    for (size_t i=0;i<v.size();++i) std::cout << (i>0 ? "," :"") << convert(v[i]);
    std::cout << "]" << std::endl;
}

std::unique_ptr<CtlFormula> get_formula(const std::string& formula_str)
{
    Lexer lexer;
    auto lex_res = lexer.lex(formula_str);
    LR1CtlParser parser(CtlParserData::grammar_ctl, ActionTable(CtlParserData::action_table_ctl_parser), GotoTable(CtlParserData::goto_table_ctl_parser));
    std::unique_ptr<CtlFormula> formula = parser.parse(lex_res);
    return formula;
}

bool test_formula(const std::string& formula_str)
{
    std::unique_ptr<CtlFormula> formula = get_formula(formula_str);
    std::cout << formula->to_string() << std::endl;
    auto aps = formula->get_aps();

    AigParser p(R"(/home/galls2/Desktop/af_ag.aig)");
    std::unique_ptr<KripkeStructure> kripke = p.to_kripke(aps);

    std::vector<ConcreteState> inits = kripke->get_initial_states();
    ConcreteState& init = inits[0];

    OmgConfigurationBuilder builder;
    OmgConfiguration config = builder.set_config_src(ConfigurationSource::DEFAULT).build();
    OmgModelChecker omg(*kripke, config);
    bool res = omg.model_checking(init, *formula);
    return res;
}
int main()
{
    const auto r1 = get_formula("p");
    const auto r2 = get_formula("p");
    int n1 = 5;
    int n2 = 5;
    auto nn1 = std::ref(n1); auto nn2 = std::ref(n2);
    std::cout << (nn1 == nn2) << std::endl;
    auto rr1 = std::reference_wrapper<const CtlFormula>(*r1);
    auto rr2 = std::reference_wrapper<const CtlFormula>(*r2);
    std::cout << (rr1 == rr2) << std::endl;
    //    bool res = test_formula(std::string("(p & state<0>) | (state<1> ^ state<0>)"));
//    std::cout << "M, s0 |" << (res ? "" : "/") << "= phi" << std::endl;

}