//
// Created by galls2 on 29/09/19.
//

#include <queue>
#include "ctl_formula.h"

std::string CtlFormula::to_string() const {
    std::string to_return = _data;

    for (const auto& op : _operands)
        to_return += " (" + op->to_string() + ") ";
    return to_return;
}

CtlFormula::CtlFormula(std::string data, std::vector<std::unique_ptr<CtlFormula>> operands) :
    _data(std::move(data)), _operands(std::move(operands)) {}

bool CtlFormula::operator==(const CtlFormula &other) const {
    if (_data != other._data || _operands.size() != other._operands.size()) return false;
    for (size_t i = 0; i < _operands.size(); ++i)
    {
        if (!(_operands[i] == other._operands[i])) return false;
    }
    return true;
}

std::unique_ptr<CtlFormula::PropertySet> CtlFormula::get_aps() const {
    std::unique_ptr<CtlFormula::PropertySet> pset = std::make_unique<CtlFormula::PropertySet>();

    std::vector<const CtlFormula*> queue;
    queue.insert(queue.begin(), this);

    while (!queue.empty())
    {
        const CtlFormula* current = queue.back();
        queue.pop_back();

        if (current->_operands.empty())
        {
            pset->emplace(current->get_data());
        }
        else
        {
            for (const auto& it : current->_operands)
            {
                queue.insert(queue.begin(), it.get());
            }
        }
    }
    return pset;
}

