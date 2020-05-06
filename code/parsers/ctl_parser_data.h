//
// Created by galls2 on 26/09/19.
//
#pragma once

#include <utility>
#include <parsers/ctl_parser.h>

/* Auto generated code starts here */
struct CtlParserData {

    static ActionTable::ActionTable_t action_table_ctl_parser;
    static GotoTable::GotoTable_t goto_table_ctl_parser;
/* Auto generated code ends here */
    static LR1CtlParser::Grammar grammar_ctl;

    typedef std::function<std::unique_ptr<CtlFormula>(std::vector<Token>, std::vector<std::unique_ptr<CtlFormula>>)> CtlFormulaCreator;
    static std::vector<CtlFormulaCreator> formula_builders;

};