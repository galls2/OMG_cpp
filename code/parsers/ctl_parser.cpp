#include "ctl_parser.h"
#include "ctl_parser_data.h"
#include  <stack>
#include <string>
#include <iostream>
#include <utils/omg_exception.h>
#include <utils/omg_utils.h>

std::unique_ptr<CtlFormula> LR1CtlParser::parse_lr(const std::vector<Token> &formula_tokens) {
    boost::variant<State, Token> initial_frame(Token(std::string("")));
    _parse_stack.emplace(0, initial_frame);
    size_t current_token_index = 0;
    while (!_parse_stack.empty())
    {
        State current_state = _parse_stack.top().first;
        Token current_token = current_token_index < formula_tokens.size() ? formula_tokens[current_token_index] : Token("$");
        auto action_table_entry_opt = _action_table.get_action(current_state, current_token);
        if (!action_table_entry_opt)
            throw CtlParserException("Parsing failed!");
        ActionTable::LrTableEntry action_table_entry = action_table_entry_opt.value();
        if (action_table_entry.is_shift())
        {
            State next_state = action_table_entry.get_index();
            _parse_stack.emplace(next_state, current_token);
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
            _parse_stack.emplace(new_state, var_derived);
        } else
        {
            assert (action_table_entry.is_accept());
            std::unique_ptr<CtlFormula> final_formula =  std::move(_formula_stack.top());
            _formula_stack.pop();
            assert(_formula_stack.empty());
            return final_formula;
        }
    }
    assert(false);
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
    assert(rule_used > 0 && rule_used <= _grammar.size());

    std::vector<std::unique_ptr<CtlFormula>> operands;
    std::vector<Token> tokens;
    size_t num_operands = 0;
     for (size_t i = 0; i < _grammar[rule_used].second.size(); ++i)
     {
         if (taken_out[i].which() == 0) // var
         {
             ++num_operands;
         }
         else
             tokens.emplace_back(boost::get<Token>(taken_out[i]));
     }
     get_operands_from_formula_stack(num_operands, operands);


     std::unique_ptr<CtlFormula> new_formula = CtlParserData::formula_builders[rule_used](std::move(tokens), std::move(operands));
     _formula_stack.emplace(std::move(new_formula));
}


std::unique_ptr<CtlFormula> LR1CtlParser::parse(const std::vector<Token> &formula_tokens) {
    std::unique_ptr<CtlFormula> lr_parsed_formula = parse_lr(formula_tokens);
    std::unique_ptr<CtlFormula> omg_formula = transform_ctl_to_omg(*lr_parsed_formula);
    return omg_formula;
}

std::unique_ptr<CtlFormula> LR1CtlParser::transform_ctl_to_omg(const CtlFormula& lr_parsed_formula)  const
{
    std::vector<std::unique_ptr<CtlFormula>> transformed_operands;
    for (const std::unique_ptr<CtlFormula>& op : lr_parsed_formula.get_operands())
    {
        transformed_operands.push_back(std::move(transform_ctl_to_omg(*op)));
    }

    if (lr_parsed_formula.get_operands().empty())
    {
        return std::make_unique<CtlFormula>(lr_parsed_formula.get_data());
    }

    std::string main_connective = lr_parsed_formula.get_data();
    if (main_connective == "EV" || main_connective == "AV") throw CtlParserException("Release is V!!!");
    const auto stay_the_same = make_array(std::string("AND"), std::string("OR"),
            std::string("ARROW"), std::string("XOR"), std::string("EX"), std::string("AR"), std::string("ER"), std::string("EQUIV"));
    // AND OR XOR OPT?
    if (std::any_of(stay_the_same.begin(), stay_the_same.end(),
            [main_connective](const std::string& op) { return op == main_connective; }))
    {
        return std::make_unique<CtlFormula>(main_connective, std::move(transformed_operands));
    }
    else if (main_connective == "NOT")
    {
        assert(transformed_operands.size() == 1);
        return do_not(std::move(transformed_operands[0]));
    }
    else
    {
        assert(main_connective.length() == 2);
        char path_quantifier = main_connective[0], temporal_operator = main_connective[1];
        switch (temporal_operator)
        {
            case 'G':
            {
                assert(transformed_operands.size() == 1);
                auto false_formula = std::make_unique<CtlFormula>("false");
                transformed_operands.emplace(transformed_operands.begin(), std::move(false_formula));
                std::string new_data = std::string(1, path_quantifier).append("R");
                return std::make_unique<CtlFormula>(new_data, std::move(transformed_operands));
            }
            case 'U':
            {
                assert(transformed_operands.size() == 2);
                std::unique_ptr<CtlFormula> op1 = std::move(transformed_operands[0]);
                std::unique_ptr<CtlFormula> op2 = std::move(transformed_operands[1]);

                auto new_op1 = do_not(std::move(op2));
                auto new_op2 = do_not(std::move(op1));
                std::vector<std::unique_ptr<CtlFormula>> release_ops;
                release_ops.emplace_back(std::move(new_op2));
                release_ops.emplace_back(std::move(new_op1));

                std::string new_data = std::string(1, 'A'+'E' - path_quantifier).append("R");
                auto release_formula = std::make_unique<CtlFormula>(new_data, std::move(release_ops));
                return do_not(std::move(release_formula));
            }
            case 'F':
            {
                assert(transformed_operands.size() == 1);
                std::unique_ptr<CtlFormula> op = std::move(transformed_operands[0]);

                auto new_op = do_not(std::move(op));
                auto false_formula = std::make_unique<CtlFormula>("false");
                std::vector<std::unique_ptr<CtlFormula>> release_ops;
                release_ops.emplace_back(std::move(false_formula));
                release_ops.emplace_back(std::move(new_op));

                std::string new_data = std::string(1, 'A'+'E' - path_quantifier).append("R");
                auto release_formula = std::make_unique<CtlFormula>(new_data, std::move(release_ops));
                return do_not(std::move(release_formula));
            }
            case 'W':
            {
                assert(transformed_operands.size() == 2);
                std::unique_ptr<CtlFormula> op1 = std::move(transformed_operands[0]);
                std::unique_ptr<CtlFormula> op2 = std::move(transformed_operands[1]);

                auto new_op1 = op2->clone();

                std::vector<std::unique_ptr<CtlFormula>> second_or_ops;
                second_or_ops.emplace_back(std::move(op1));
                second_or_ops.emplace_back(std::move(op2));

                auto new_op2 = std::make_unique<CtlFormula>("OR", std::move(second_or_ops));

                std::vector<std::unique_ptr<CtlFormula>> release_ops;
                release_ops.emplace_back(std::move(new_op1));
                release_ops.emplace_back(std::move(new_op2));

                std::string new_data = std::string(1, path_quantifier).append("R");

                auto release_formula = std::make_unique<CtlFormula>(new_data, std::move(release_ops));
                return release_formula;
            }
            case 'X':
            {
                assert(path_quantifier == 'A'); // We are AX inner. We should be NOT EX NOT inner.
                assert(transformed_operands.size() == 1);
                std::unique_ptr<CtlFormula> inner = std::move(transformed_operands[0]);
                auto to_not_ex = do_not(std::move(inner));

                std::vector<std::unique_ptr<CtlFormula>> ex_ops;
                ex_ops.emplace_back(std::move(to_not_ex));
                auto ex_formula = std::make_unique<CtlFormula>("EX", std::move(ex_ops));

                return do_not(std::move(ex_formula));
            }
            default:
                assert(false);
        }
    }
}

std::unique_ptr<CtlFormula> LR1CtlParser::do_not(std::unique_ptr<CtlFormula> f) const
{
    // If f = NOT g, we return g. otherwise, return NOT f to become NOT EX g.
    if (f->get_data() == "NOT") {
        return std::make_unique<CtlFormula>(std::move(*(f->get_operands()[0])));
    } else {
        std::vector<std::unique_ptr<CtlFormula>> to_not_ex_ops;
        to_not_ex_ops.emplace_back(std::move(f));
        return std::make_unique<CtlFormula>("NOT", std::move(to_not_ex_ops));
    }
}
