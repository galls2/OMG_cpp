#pragma once
#include <unordered_map>
#include <string>

class VersionManager
{
public:
    static std::string new_version(const std::string& orig_name);
    static std::string new_version(const size_t orig_name);
    static void reset();
    static const char DELIM = '$';
private:
    static std::unordered_map<std::string, size_t> _copies_counter;

};
