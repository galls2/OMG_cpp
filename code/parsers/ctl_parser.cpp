#include "ctl_parser.h"
#include  <stack>
#include <string>
#include <iostream>
#include <utils/omg_exception.h>
std::unique_ptr<CtlFormula> LR1CtlParser::parse(const std::vector<Token> &formula_tokens) {
    boost::variant<State, Token> initial_frame(Token(std::string("")));
    _parse_stack.push(std::make_pair(0, initial_frame));
    size_t current_token_index = 0;
    while (!_parse_stack.empty())
    {
        State current_state = _parse_stack.top().first;
        Token current_token = formula_tokens[current_token_index];
        auto action_table_entry_opt = _action_table.get_action(current_state, current_token);
        if (!action_table_entry_opt)
            throw std::runtime_error("Parsing failed!");
        ActionTable::LrTableEntry action_table_entry = action_table_entry_opt.value();
        std::cout << action_table_entry << std::endl;
        if (action_table_entry.is_shift())
        {
            State next_state = action_table_entry.get_index();
            _parse_stack.push(std::make_pair(next_state, current_token));
            ++current_token_index;
        }
        else
        {
            assert(action_table_entry.is_reduce());
            GrammarRule& grammar_rule = _grammar[action_table_entry.get_index()];
            size_t rule_result_length = grammar_rule.second.size();
            VarName var_derived = grammar_rule.first;

            for (size_t i = 0; i < rule_result_length; ++i) { _parse_stack.pop(); }
            State stack_head_state = _parse_stack.top().first;

            State new_state = _goto_table.go_to(stack_head_state, var_derived);
            _parse_stack.push(std::make_pair(new_state, var_derived));

            std::cout<< "Rule " << action_table_entry.get_index() << " was used!" << std::endl;

        }

    }
}
