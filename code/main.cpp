//
// Created by galls2 on 30/08/19.
#include <fstream>
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
#include <chrono>
//#include <boost/thread/thread.hpp>

#define TEST(aig_path, raw_ctl_string, expected) \
    do \
        { \
            auto t1 = std::chrono::high_resolution_clock::now(); \
            bool passed = ((expected) == test_formula(std::string((aig_path)), std::string((raw_ctl_string)))); \
            if (passed) std::cout << "PASS! :)" << std::endl; \
            else std::cout << "\tFAIL!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl; \
            auto t2 = std::chrono::high_resolution_clock::now(); \
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>( t2 - t1 ).count(); \
            std::cout << "Time: " << duration << std::endl; \
        } \
    while(0)

#define PRINT_IF_BUG(actual_res, expected_res, aig, spec, spec_num) \
    do \
    { \
        bool passed = ((expected_res) == (actual_res)); \
        if (passed) std::cout << "Spec #" << spec_num << ": PASS! :)" << std::endl; \
        else std::cout << "Spec #" << spec_num << ":\tFAIL!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! Failed while checking " << aig << " with " << spec << std::endl; \
    } \
    while(0)

std::vector<FormulaChunk> get_formula_chunks(const std::string& ctl_file_path)
{
    CtlFileParser ctl_file_parser;
    std::vector<FormulaChunk> formula_chunks;
    ctl_file_parser.parse_ctl_file(ctl_file_path, formula_chunks);
    return formula_chunks;
}

void test_parser_with_model(const std::string& model_name)
{
    std::cout << "Parsing " <<model_name << "... ";
    try
    {
        std::vector<FormulaChunk> formula_chunks = get_formula_chunks(model_name);
        std::cout << "Success!" << std::endl;
    }
    catch(std::exception& ex)
    {
        std::cout << "Failed!" << std::endl;
//        std::cout << ex.what() << std::endl;
    }
}

void test_parser(const std::string& file_path)
{
    std::ifstream infile(file_path.c_str());

    std::string line;
    while (std::getline(infile, line))
    {
        std::string model_name = std::string("../resources/") + line.substr(0, line.length() -4);
        const std::string &ctl_file_path = model_name + ".ctl";
        test_parser_with_model(ctl_file_path);

    }
}




void test_model(const std::string& file_path_no_extension) {
    std::cout << "Testing model: " << file_path_no_extension << std::endl;
    const std::string &aig_path = file_path_no_extension + ".aig";
    const std::string &ctl_file_path = file_path_no_extension + ".ctl";

    OmgConfigBuilder builder;
    builder.set_config_src(ConfigurationSource::FILE).set_config_file_path("../run_config.omg").build();
    DEBUG_PRINT("OMG Configuration:\n %s",OmgConfig::config_table_to_string().data());

    AigParser p(aig_path);

    std::vector<FormulaChunk> formula_chunks = get_formula_chunks(ctl_file_path);

    uint16_t prop_count = 0;
    if (!OmgConfig::get<bool>("Properties per specification")) {
        CtlFormula::PropertySet APs;
        DEBUG_PRINT("Chunk Structure:\n");
        for (const auto &it : formula_chunks) {
            DEBUG_PRINT("BEGIN CHUNK! Result it %s.\n", it.get_expected_result() ? "Pass" : "Fail");
            for (const auto &it2 : it.get_formulas()) {
                DEBUG_PRINT("\tFormula: %s\n", it2->to_string().data());
                CtlFormula::PropertySet current_aps = it2->get_aps();
                APs.insert(current_aps.begin(), current_aps.end());
            }
            DEBUG_PRINT("END CHUNK!");
        }

        auto t1 = std::chrono::high_resolution_clock::now();

        std::unique_ptr<KripkeStructure> kripke = p.to_kripke(APs);

        OmgModelChecker omg(*kripke);
        auto t2 = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>( t2 - t1 ).count();
        std::cout << "MC Time: " << duration << std::endl;

        for (const auto &it : formula_chunks) {
            bool is_pass = it.get_expected_result();
            for (const auto &it2 : it.get_formulas()) {
                DEBUG_PRINT("Testing ## %s ## against ## %s ##... ", it2->to_string().data(), aig_path.data());
                auto t11 = std::chrono::high_resolution_clock::now();

                bool res = omg.check_all_initial_states(*it2);

                auto t21 = std::chrono::high_resolution_clock::now();
                auto duration1 = std::chrono::duration_cast<std::chrono::milliseconds>( t21 - t11 ).count();

                PRINT_IF_BUG(res, is_pass, aig_path, it2->to_string(), prop_count);
                std::cout << "MC Time: " << duration1 << std::endl;

                ++prop_count;
            }
        }
    } else {
        for (const FormulaChunk &chunk : formula_chunks) {
            bool is_pass = chunk.get_expected_result();
            for (const auto &it : chunk.get_formulas()) {

                DEBUG_PRINT("Testing ## %s ## against ## %s ##... ", it->to_string().data(), aig_path.data());
                auto t1 = std::chrono::high_resolution_clock::now();

                std::unique_ptr<KripkeStructure> kripke = p.to_kripke(it->get_aps());
                OmgModelChecker omg(*kripke);

                bool res = omg.check_all_initial_states(*it);
                auto t2 = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::milliseconds>( t2 - t1 ).count();
                std::cout << "Ctr + MC Time: " << duration << std::endl;
                PRINT_IF_BUG(res, is_pass, aig_path, it->to_string(), prop_count);

                ++prop_count;
            }
        }
    }
    Z3_finalize_memory();

}



/*
 * THIS IS FOR UNIT TESTS
 */
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

    OmgConfigBuilder builder;
    builder.set_config_src(ConfigurationSource::FILE).set_config_file_path("../run_config.omg").build();


    std::unique_ptr<CtlFormula> formula = get_formula(formula_str);
    auto aps = formula->get_aps();

    AigParser p(aig_path);
    std::unique_ptr<KripkeStructure> kripke = p.to_kripke(aps);

    OmgModelChecker omg(*kripke);
    bool res = omg.check_all_initial_states(*formula);

    std::cout << "Done. ";

    Z3_finalize_memory();
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

void unit_tests_av()
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
    TEST("../resources/tstrst.aig", "AG (o | ~t | s)", true);
    TEST("../resources/gatedClock.aig", "AG(r0 -> AX r1)", true);

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

void unit_tests_ev()
{
    TEST("../resources/af_ag.aig", "EG ((~state<0>) & (~state<1>))", true);
    TEST("../resources/af_ag.aig", "EX EG (state<0> ^ state<1>)", true);
    TEST("../resources/af_ag.aig", "AX EG ~state<1>", false);
    TEST("../resources/af_ag.aig", "EF EG ((~state<0>) & state<1>)", true);
    TEST("../resources/af_ag.aig", "AF AG p", false);

    TEST("../resources/debug.aig", "AF AG ~a", true);
    TEST("../resources/debug.aig", "AF AG a", false);
}


void unit_tests()
{
    unit_tests_aps();
    unit_tests_modal();
    unit_tests_av();
    unit_tests_ev();
}

void run_models(const std::string& file_path)
{
    std::ifstream infile(file_path.c_str());

    std::string line;
    while (std::getline(infile, line))
    {
        std::string model_name = std::string("../resources/") + line.substr(0, line.length() -4);
        test_model(model_name);
    }
}

void test_parser_s(const std::string& s)
{
    Lexer lexer;
    LR1CtlParser parser(CtlParserData::grammar_ctl, ActionTable(CtlParserData::action_table_ctl_parser), GotoTable(CtlParserData::goto_table_ctl_parser));
    auto lex_result = lexer.lex(s);
    auto parse_result = parser.parse(lex_result);
    std::cout << "5";
}

//
//void test_f()
//{
//    int o = 0;
//    while(true)
//    {
//        o++;
//        if (o % 10000 == 0) { std::cout << "I"; o = 0; }
//    }
//}
//
//void thread_test()
//{
//    boost::thread t([]() { test_f(); });
//    bool res = t.timed_join(boost::posix_time::seconds(1));
//    std::cout << res << std::endl;
//}
int main()
{
//    run_models("../models_to_run.omg");
  //  test_model("../resources/cp0IntEncoder");
//    unit_tests();
//    TEST("../resources/spinner4.aig", "AG((~inr<3> & ~inr<2> & ~inr<1> & inr<0>) -> ~E spl U (~inr<3> & ~inr<2> & inr<1> & inr<0>))", false);
    TEST("../resources/twophase.aig", "AG ~out", false);


//    thread_test();

}

/*
 * Bad examples:
 *  rrobin - we develop all reachable states, as a non-reachable state requires a lot of refining to exclude. TOO MANY APs matter
 */