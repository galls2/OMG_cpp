#include <utility>

#include <utility>

#pragma once
#include <vector>
#include <string>
#include <memory>

class FormulaComponent{};
enum class PathQuantifier
{ A, E };

enum class TemporalOperator
{ F, G, V, W, U };

enum class LogicalOperator
{ AND, OR, NOT, XOR };

class CtlFormula
{
public:
  CtlFormula(std::vector<FormulaComponent> data, std::vector<std::unique_ptr<CtlFormula>> operands) :
    _data(std::move(data)), _operands(std::move(operands)) {}

private:
  std::vector<FormulaComponent> _data;
  std::vector<std::unique_ptr<CtlFormula>> _operands;
};
