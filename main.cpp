//
// Created by galls2 on 30/08/19.
//
#include <iostream>
#include <parsers/aig_parser.h>
#include <parsers/ctl_parser.h>
#include <parsers/lexer.h>
#include <parsers/ctl_parser_data.h>
#include <parsers/ctl_file_parser.h>
#include <unordered_set>
#include <model_checking/omg_model_checker.h>
#include <utils/omg_utils.h>
#include <utils/z3_utils.h>

#define TEST(aig_path, raw_ctl_string, expected) \
    do \
        { \
            bool passed = ((expected) == test_formula(std::string((aig_path)), std::string((raw_ctl_string)))); \
            if (passed) std::cout << "PASS! :)" << std::endl; \
            else std::cout << "\tFAIL!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl; \
        } \
    while(0)


void test_ctl_file_parser()
{
    CtlFileParser ctl_file_parser;
    std::vector<FormulaChunk> formula_chunks;
    ctl_file_parser.parse_ctl_file("../resources/spm.ctl", formula_chunks);
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

bool test_formula(const std::string& aig_path, const std::string& formula_str)
{
    std::cout << "Testing ##" << formula_str << "## against ##" << aig_path << "##... ";

    std::unique_ptr<CtlFormula> formula = get_formula(formula_str);
    auto aps = formula->get_aps();

    AigParser p(aig_path);
    std::unique_ptr<KripkeStructure> kripke = p.to_kripke(aps);

    std::vector<ConcreteState> inits = kripke->get_initial_states();
    ConcreteState& init = inits[0];

    OmgConfigBuilder builder;
    builder.set_config_src(ConfigurationSource::DEFAULT).build();
    OmgModelChecker omg(*kripke);
    bool res = omg.model_checking(init, *formula);

    std::cout << "Done. ";
    return res;

}

void unit_tests_aps()
{
    TEST("../resources/af_ag.aig", "!state<0>", true);
    TEST("../resources/af_ag.aig", "!state<1>", true);
    TEST("../resources/af_ag.aig", "state<0>", false);
    TEST("../resources/af_ag.aig", "state<1>", false);
    TEST("../resources/af_ag.aig", "p", true);
    TEST("../resources/af_ag.aig", "(state<1> | state<0>)", false);
    TEST("../resources/af_ag.aig", "(p | state<0>)", true);
    TEST("../resources/af_ag.aig", "!p", false);
    TEST("../resources/af_ag.aig", "(p & state<0>)", false); //
    TEST("../resources/af_ag.aig", "(state<1> ^ state<0>)", false);
    TEST("../resources/af_ag.aig", "((((((state<1>)) ^ (state<0>)))))", false);
    TEST("../resources/af_ag.aig", "(p & state<0>) | (state<1> ^ state<0>)", false);
    TEST("../resources/af_ag.aig", " (~state<0>) | state<1>", true);
    TEST("../resources/af_ag.aig", " (~state<0>) & state<1>", false);
    TEST("../resources/af_ag.aig", " (~state<0>) &  (!state<1>)", true);
    TEST("../resources/gray.aig", "true", true);
    TEST("../resources/gray.aig", "false", false);
}

void unit_tests_ag()
{
    TEST("../resources/af_ag.aig", "AG ((~state<0>) | (~state<1>))", true);
    TEST("../resources/af_ag.aig", "AG ((~state<0>) & (~state<1>))", false);
    TEST("../resources/af_ag.aig", "AG (~state<0>) ", false);
    TEST("../resources/af_ag.aig", "AG (~state<1>) ", false);
    TEST("../resources/af_ag.aig", "AG (!(state<0> & state<1>))", true);
    TEST("../resources/af_ag.aig", "AG (state<0> | state<1>)", false);

    TEST("../resources/gray.aig", "AG ((~p) & (~q) & (~r))", false);
    TEST("../resources/gray.aig", "AG (~p)", false);
    TEST("../resources/gray.aig", "AG (~q)", false);
    TEST("../resources/gray.aig", "AG (~r)", false);
    TEST("../resources/gray.aig", "AG (~((~p) & (~q) & r))", true);
    TEST("../resources/gray.aig", "AG (~((~p) & q & (!r)))", true);
    TEST("../resources/gray.aig", "AG (~(p & (!q) & (r)))", true);
    TEST("../resources/gray.aig", "AG (~(p & (q) & (!r)))", true);
    TEST("../resources/gray.aig", "((~q) & (~r)) -> (~(E (~p) U r))", true);

//    TEST("../resources/af_ag.aig", "AG true", true); // This should fail, as AP is empty, which is not allowed
}


void unit_tests_modal()
{

    TEST("../resources/af_ag.aig", "EX (state<0> & ~state<1>)", true);
    TEST("../resources/af_ag.aig", "EX ~state<0> & ~state<1>", true);
    TEST("../resources/af_ag.aig", "EX state<0> & state<1>", false);
    TEST("../resources/af_ag.aig", "EX state<0> | state<1>", true);
    TEST("../resources/af_ag.aig", "EX (~state<0>) & state<1>", false);
    TEST("../resources/af_ag.aig", "EX state<1>", false);
    TEST("../resources/af_ag.aig", "EX EX ((~state<0>) & state<1>)", true);
    TEST("../resources/af_ag.aig", "EX ((EX ((~state<0>) & state<1>)) | (EX (state<0> & state<1>)))", true);
    TEST("../resources/af_ag.aig", "EX EX ((~state<0>) & state<1>)", true);
    TEST("../resources/af_ag.aig", "EX EX (state<0> & state<1>)", false);
    TEST("../resources/af_ag.aig", "EX EX EX (state<0> & state<1>)", false);
    TEST("../resources/af_ag.aig", "AX !state<1>", true);
    TEST("../resources/af_ag.aig", "AX state<0>", false);
    TEST("../resources/af_ag.aig", "AX (p)", false);

}

void unit_tests_complex()
{

}

void unit_tests()
{
    unit_tests_aps();
    unit_tests_modal();
    unit_tests_ag();

}

int main()
{
    unit_tests();
//    TEST("../resources/gray.aig", "((~q) & (~r)) -> (~(E (~p) U r))", true);

 // The bug appears when you run unit_test() in the last property in AG
 // If ran there, there is no inductiveness after 1 unwinding, and so we continue and then rechoose a node in the tree.
 // However, if ran regularly, we do find inductiveness and finish

 // The truth: initial states has two successors: itself and another one that satisfies (~p), which is p in ApVq.
 // Thus, there it is not checked for clousre, and Abs0 does have closure, so closure SHOULD in fact be found after one
 // iteration. Thus, the "regular run is OK", answering:
 // First, ran regularly, why would there be closure for Abs 0 when there wasn't before?

 // We still seek closure for Abs1, even though we shouldn't. Then there is indeed no closure, and we choose someone else.
 // However we still explore [1 0 0 1]

 // We should now answer why it happens that:
 // Then, why is there a rechoosing when running ALL?
 // This makes sense, as closure was not found, we seek to further develop this node's suceesors, but as it satisfies p there aren't any and it is rechosen.

 // And then, why wasn't a closure found??
 // Why is there a difference?
}
