//
// Created by galls2 on 17/09/19.
//

#include <cassert>
#include <unordered_map>
#include "version_manager.h"
#include "string_utils.h"

std::unordered_map<std::string, size_t> VersionManager::_copies_counter = {};


std::string VersionManager::new_version(const std::string &orig_name)
{
    if (orig_name.find(DELIM) == std::string::npos)
    {
        assert(_copies_counter.find(orig_name) == _copies_counter.end());
        _copies_counter[orig_name] = 0;
        return orig_name + std::to_string(DELIM) +"0";
    }
    else
    {
        std::array<std::string, 2> parts = split_to<2>(orig_name, DELIM);
        return parts[0] + std::to_string(DELIM) + std::to_string(++_copies_counter[parts[0]]);
    }
}

std::string VersionManager::new_version(const size_t orig_name) {
    return VersionManager::new_version(std::to_string(orig_name));
}
