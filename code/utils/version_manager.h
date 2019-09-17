#pragma once
#include <map>
#include <string>

class VersionManager
{
public:
    static std::string new_version(const std::string& orig_name);
private:
    static std::map<std::string, size_t> _copies_counter;
};
