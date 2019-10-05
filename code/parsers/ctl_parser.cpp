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
        Token current_token = current_token_index < formula_tokens.size() ? formula_tokens[current_token_index] : Token("$");
        auto action_table_entry_opt = _action_table.get_action(current_state, current_token);
        if (!action_table_entry_opt)
            throw std::runtime_error("Parsing failed!");
        ActionTable::LrTableEntry action_table_entry = action_table_entry_opt.value();
        if (action_table_entry.is_shift())
        {
            State next_state = action_table_entry.get_index();
            _parse_stack.push(std::make_pair(next_state, current_token));
            ++current_token_index;
        }
        else if (action_table_entry.is_reduce())
        {
            size_t used_rule_number = action_table_entry.get_index();
            GrammarRule& grammar_rule = _grammar[used_rule_number];
            size_t rule_result_length = grammar_rule.second.size();
            VarName var_derived = grammar_rule.first;

            std::vector<GrammarRuleEntity> taken_out;
            for (size_t i = 0; i < rule_result_length; ++i)
            {
                taken_out.push_back(_parse_stack.top().second);
                _parse_stack.pop();
            }
            handle_formula_stack(used_rule_number, taken_out);

            State stack_head_state = _parse_stack.top().first;

            State new_state = _goto_table.go_to(stack_head_state, var_derived);
            _parse_stack.push(std::make_pair(new_state, var_derived));
        } else
        {
            assert (action_table_entry.is_accept());
            std::unique_ptr<CtlFormula> final_formula =  std::move(_formula_stack.top());
            _formula_stack.pop();
            assert(_formula_stack.empty());
            return final_formula;
        }
    }
}
void LR1CtlParser::get_operands_from_formula_stack(size_t num_operands, std::vector<std::unique_ptr<CtlFormula>>& to_fill)
{
    for (size_t i = 0; i < num_operands; ++i)
    {
        to_fill.emplace(to_fill.begin(), std::move(_formula_stack.top()));
        _formula_stack.pop();
    }
}
void LR1CtlParser::handle_formula_stack(size_t rule_used, const std::vector<GrammarRuleEntity> &taken_out) {
    assert(taken_out.size() == _grammar[rule_used].second.size());
    if (rule_used <= 0)
    {
        assert(false);
    }
    else if (rule_used == 1)
    {
        const Token& ap_token = boost::get<Token>(taken_out[0]);
        assert(ap_token.get_token_type().get_data() == std::string("AP"));
        assert(ap_token.is_ap());
        std::string ap_text = ap_token.get_data();
        std::unique_ptr<CtlFormula> formula = std::make_unique<CtlFormula>(ap_text);
        _formula_stack.emplace(std::move(formula));
    }
    else if (rule_used >= 2 && rule_used <= 5)
    {
        std::string logical_operand = boost::get<Token>(taken_out[1]).get_data();

        std::vector<std::unique_ptr<CtlFormula>> operands;
        get_operands_from_formula_stack(2, operands);

        std::unique_ptr<CtlFormula> formula = std::make_unique<CtlFormula>(logical_operand, std::move(operands));
        _formula_stack.emplace(std::move(formula));
    }
    else if (rule_used == 6)
    {
        std::vector<std::unique_ptr<CtlFormula>> operands;
        get_operands_from_formula_stack(1, operands);

        std::unique_ptr<CtlFormula> formula = std::make_unique<CtlFormula>("NOT", std::move(operands));
        _formula_stack.emplace(std::move(formula));
    }
    else if (rule_used == 7)
    {
        std::vector<std::unique_ptr<CtlFormula>> operands;

        std::vector<std::unique_ptr<CtlFormula>> out_formulas;
        get_operands_from_formula_stack(3, out_formulas);

        std::unique_ptr<CtlFormula> operand(std::move(out_formulas.back()));
        out_formulas.pop_back();

        std::unique_ptr<CtlFormula> temporal_operator(std::move(out_formulas.back()));
        out_formulas.pop_back();

        std::unique_ptr<CtlFormula> path_quantifier(std::move(out_formulas.back()));
        out_formulas.pop_back();


        operands.emplace(operands.begin(), std::move(operand));

        std::unique_ptr<CtlFormula> formula = std::make_unique<CtlFormula>((*path_quantifier).get_data()+(*temporal_operator).get_data(), std::move(operands));
        _formula_stack.emplace(std::move(formula));
    }
    else if (rule_used == 8)
    {
        std::vector<std::unique_ptr<CtlFormula>> operands;

        std::vector<std::unique_ptr<CtlFormula>> out_formulas;
        get_operands_from_formula_stack(4, out_formulas);

        std::unique_ptr<CtlFormula> second_operand(std::move(out_formulas.back()));
        out_formulas.pop_back();

        std::unique_ptr<CtlFormula> temporal_operator(std::move(out_formulas.back()));
        out_formulas.pop_back();

        std::unique_ptr<CtlFormula> first_operand(std::move(out_formulas.back()));
        out_formulas.pop_back();

        std::unique_ptr<CtlFormula> path_quantifier(std::move(out_formulas.back()));
        out_formulas.pop_back();


        operands.emplace(operands.begin(), std::move(second_operand));
        operands.emplace(operands.begin(), std::move(first_operand));

        std::unique_ptr<CtlFormula> formula = std::make_unique<CtlFormula>((*path_quantifier).get_data()+(*temporal_operator).get_data(), std::move(operands));
        _formula_stack.emplace(std::move(formula));
    }
    else if (rule_used >= 9 && rule_used <= 16)
    {
        std::string op = boost::get<Token>(taken_out[0]).get_data();
        std::unique_ptr<CtlFormula> formula = std::make_unique<CtlFormula>(op);
        _formula_stack.emplace(std::move(formula));
    }
    else
    {
        assert(rule_used == 17);
        // DO NOTHING
    }
}
