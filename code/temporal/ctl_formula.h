#pragma once
#include <vector>
#include <string>
#include <memory>
#include <utility>

class CtlFormula
{
public:
    explicit CtlFormula(std::string data, std::vector<std::unique_ptr<CtlFormula>> operands={}) :
    _data(std::move(data)), _operands(std::move(operands)) {}

    std::string get_data() const { return _data; }
    std::string to_string() const;
private:
  std::string _data;
  std::vector<std::unique_ptr<CtlFormula>> _operands;
};
