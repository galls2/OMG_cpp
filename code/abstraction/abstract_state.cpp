//
// Created by galls2 on 12/10/19.
//

#include <algorithm>
#include <iterator>
#include "abstract_state.h"

AbstractState::AbstractState(const KripkeStructure &kripke, std::unique_ptr<CtlFormula::PropertySet> pos_labels,
                             const CtlFormula::PropertySet& atomic_labels, PropFormula sym_rep)
                             : _kripke(kripke), _pos_labels(std::move(pos_labels)), _atomic_labels(atomic_labels),
                                     _sym_rep(std::move(sym_rep))
{
    std::set<std::string> all_str = CtlFormula::property_set_to_string_set(_atomic_labels);
    std::set<std::string> pos_str = CtlFormula::property_set_to_string_set(_atomic_labels);
    std::set<std::string> neg_str;
    std::set_difference(all_str.begin(), all_str.end(), pos_str.begin(), pos_str.end(),
                        std::inserter(neg_str, neg_str.end()));
    for (const std::string& ap_str : neg_str) _neg_labels->emplace(ap_str);
}

bool AbstractState::operator<(const AbstractState &other) const {
    return _cl_node < other._cl_node;
}
