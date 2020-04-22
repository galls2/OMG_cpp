#include <utility>

#pragma once

#include <string>
#include <unordered_map>
#include <utils/omg_exception.h>
#include <boost/variant.hpp>
#include <utility>


DECLARE_OMG_EXCEPTION(OmgConfigException)

typedef std::unordered_map<std::string, boost::variant<std::string, bool, int>> ConfigTable;

class OmgConfigBuilder;

struct OmgConfig {
    friend class OmgConfigurationBuilder;

    template <typename T>
    static const T& get(const std::string& key);

    static void load_config_table(ConfigTable conf_table) { OmgConfig::_configuration = std::move(conf_table); };

    static std::string config_table_to_string();
private:
    static ConfigTable _configuration;
};

enum class ConfigurationSource
{
    STDIN, FILE, DEFAULT
};

enum class ValueType
{
    BOOLEAN, NUMERIC, STRING
};


class OmgConfigBuilder
{
public:
    OmgConfigBuilder(): _config_src(ConfigurationSource::FILE), _config_file_path("config.omg") {};

    OmgConfigBuilder& set_config_src(ConfigurationSource config_src) { _config_src = config_src; return *this; }
    OmgConfigBuilder& set_config_file_path(const std::string &config_file_path) { _config_file_path = config_file_path; return *this; }

    static std::unordered_map<std::string, ValueType> configuration_fields;

    void build();
private:
    ConfigurationSource _config_src;
    std::string _config_file_path;


    ConfigTable get_config_from_file() const;
};

template<typename T>
const T &OmgConfig::get(const std::string &key) {
    return boost::get<T>(OmgConfig::_configuration.at(key));
}

