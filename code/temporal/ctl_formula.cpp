//
// Created by galls2 on 29/09/19.
//

#include "ctl_formula.h"

std::string CtlFormula::to_string() const {
    std::string to_return = _data;

    for (const auto& op : _operands)
        to_return += " (" + op->to_string() + ") ";
    return to_return;
}
