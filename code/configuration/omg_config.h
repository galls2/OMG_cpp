#pragma once

#include <string>
#include <unordered_map>
#include <utils/omg_exception.h>
#include <boost/variant.hpp>
#include <utility>


DECLARE_OMG_EXCEPTION(OmgConfigurationException)

typedef std::unordered_map<std::string, boost::variant<bool, int, std::string>> ConfigTable;

class OmgConfigurationBuilder;

struct OmgConfiguration {
    ConfigTable _configuration;
    friend class OmgConfigurationBuilder;

    template <typename T>
    const T& get(const std::string& key) const;

private:
    explicit OmgConfiguration(ConfigTable configuration_data) : _configuration(std::move(configuration_data)) {}

};

enum class ConfigurationSource
{
    STDIN, FILE, DEFAULT
};

enum class ValueType
{
    BOOLEAN, NUMERIC, STRING
};


class OmgConfigurationBuilder
{
public:
    OmgConfigurationBuilder(): _config_src(ConfigurationSource::FILE), _config_file_path("config.omg") {};

    OmgConfigurationBuilder& set_config_src(ConfigurationSource config_src) { _config_src = config_src; return *this; }
    OmgConfigurationBuilder& set_config_file_path(const std::string &config_file_path) { _config_file_path = config_file_path; return *this; }

    OmgConfiguration build();
private:
    ConfigurationSource _config_src;
    std::string _config_file_path;

    static std::unordered_map<std::string, ValueType> configuration_fields;

    OmgConfiguration get_config_from_file() const;
};

template<typename T>
const T &OmgConfiguration::get(const std::string &key) const {
    return boost::get<T>(_configuration.at(key));
}
