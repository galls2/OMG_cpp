#pragma once
#include <string>
#include <memory>
#include <vector>
#include <temporal/ctl_formula.h>

class ACtlParser
{
public:
  std::unique_ptr<CtlFormula> parse(const std::string& raw_formula) = 0;
};



class LR1CtlParser : public ACtlParser
{
public:
  enum class LrAction { SHIFT, REDUCE };

  std::unique_ptr<CtlFormula> parse(const std::string& raw_formula);

  static constexpr std::vector<std::pair <char, std::string>> grammar_rules = {};
};
