#pragma once
#include <vector>
#include <string>
#include <set>
#include <memory>
#include <utility>
#include <unordered_set>


class CtlFormula
{
public:

    struct CtlFormulaHasher
    {
        size_t operator()(const CtlFormula& a) const
        {
            std::hash<std::string> hasher;
            return hasher(a.to_string());
        }

    };

    typedef std::unordered_set<CtlFormula, CtlFormulaHasher> PropertySet;

    explicit CtlFormula(std::string data, std::vector<std::unique_ptr<CtlFormula>> operands = {});

    std::string get_data() const;
    std::string to_string() const;
    bool operator==(const CtlFormula& other) const;
    std::unique_ptr<PropertySet> get_aps() const;
    bool is_boolean() const;
    bool get_boolean_value() const;
    const std::vector<std::unique_ptr<CtlFormula>>& get_operands() const;

    bool operator<(const CtlFormula& other) const;


    static std::set<std::string> property_set_to_string_set(const PropertySet& property_set);
private:
  std::string _data;
  std::vector<std::unique_ptr<CtlFormula>> _operands;
};



