#include "ctl_parser.h"
#include  <stack>
#include <iostream>

std::unique_ptr<CtlFormula> LR1CtlParser::parse(const std::vector<Token> &formula_tokens) {
    _parse_stack.push(std::make_pair(0, ""));
    size_t current_token_index = 0;
    while (!_parse_stack.empty())
    {
        State current_state = _parse_stack.top().first;
        Token current_token = formula_tokens[current_token_index];
        LrTable::LrTableEntry lr_table_entry = _lr_table[current_state, current_token];
        if (lr_table_entry.is_shift())
        {
            _parse_stack.push(std::make_pair(current_state, current_token));
            ++current_token_index;
        }
        else
        {
            assert(lr_table_entry.is_reduce());
            GrammarRule& grammar_rule = _grammar[lr_table_entry.get_index()];
            size_t rule_result_length = grammar_rule.second.size();
            VarName var_derived = grammar_rule.first;

            for (size_t i = 0; i < rule_result_length; ++i) { _parse_stack.pop(); }
            State stack_head_state = _parse_stack.top().first;

            State new_state = _goto_table.go_to(stack_head_state, var_derived);
            _parse_stack.push(std::make_pair(new_state, var_derived));

            std::cout<< "Rule " << lr_table_entry.get_index() << " was used!" << std::endl;

        }

    }
}
