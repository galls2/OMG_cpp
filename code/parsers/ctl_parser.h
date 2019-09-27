#pragma once

#include <string>
#include <map>
#include <memory>
#include <utility>
#include <stack>
#include <unordered_map>
#include <boost/variant.hpp>
#include <vector>
#include <experimental/optional>
#include <temporal/ctl_formula.h>
#include <utils/omg_exception.h>
#include "lexer.h"

class ACtlParser
{
public:
    virtual std::unique_ptr<CtlFormula> parse(const std::vector<Token>& formula_tokens) = 0;
};

typedef char VarName;
typedef boost::variant<VarName, Token> GrammarRuleEntity;
typedef size_t State;



struct ActionTable
{
    enum class LrAction { SHIFT, REDUCE, ACCEPT };
    struct LrTableEntry{
        LrAction _action;
        size_t _index;
        LrTableEntry(const LrAction action, const State index) : _action(action), _index(index) {}
        size_t get_index() const { return _index; }
        bool is_shift() const { return _action == LrAction::SHIFT; }
        bool is_reduce() const { return _action == LrAction::REDUCE; }
        friend std::ostream& operator<<(std::ostream& os, const LrTableEntry& entry)
        {
            os << ((entry._action == LrAction::SHIFT) ? ("SHIFT") : (entry._action == LrAction::REDUCE ? "REDUCE" : "ACCEPT")) << entry._index;
            return os;
        }
    };

    typedef std::map<std::pair<State, Token>, LrTableEntry> ActionTable_t;

    std::experimental::optional<LrTableEntry> get_action(const State& state, const Token& token) const
    {
       if (_table_data.find(std::make_pair(state, token.get_token_type())) != _table_data.end())
       {
            return std::experimental::optional<LrTableEntry>(_table_data.at(std::make_pair(state, token.get_token_type())));
       }
       else return std::experimental::optional<LrTableEntry>();
    }

    explicit ActionTable(ActionTable_t table_data) : _table_data(std::move(table_data)) {}

private:
    ActionTable_t _table_data;
};


struct GotoTable
{

    typedef std::map<std::pair<State, VarName>, State> GotoTable_t;

    State go_to(const State& state, const VarName& var_name) const
    {
        return _table_data.at(std::make_pair(state, var_name));
    }
    GotoTable(GotoTable_t table_data) : _table_data(std::move(table_data)) {}

private:
    GotoTable_t _table_data;
};

class LR1CtlParser : public ACtlParser
{

public:
  typedef std::pair<VarName, std::vector<GrammarRuleEntity>> GrammarRule;
  typedef std::vector<GrammarRule> Grammar;

  LR1CtlParser(Grammar grammar, ActionTable action_table, GotoTable goto_table) :
  _grammar(std::move(grammar)), _action_table(std::move(action_table)), _goto_table(std::move(goto_table)) {}

  virtual std::unique_ptr<CtlFormula> parse(const std::vector<Token>& formula_tokens) override;
    virtual ~LR1CtlParser() {}
private:
    Grammar _grammar;
    ActionTable _action_table;
    GotoTable _goto_table;
    std::stack<std::pair<State, GrammarRuleEntity>> _parse_stack;
    std::stack<CtlFormula> _formula_stack;
};

