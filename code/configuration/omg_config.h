#include <utility>

#include <utility>

//
// Created by galls2 on 29/09/19.
//

#ifndef OMG_CPP_OMG_CONFIG_H
#define OMG_CPP_OMG_CONFIG_H

#include <string>
#include <unordered_map>

//class OmgConfigurationException : OmgException { using OmgException::OmgException; };
DECLARE_OMG_EXCEPTION(OmgConfigurationException)


struct OmgConfiguration {
    std::unordered_map<std::string, std::string> configuration;

private:
    explicit OmgConfiguration(std::unordered_map<std::string, std::string> configuration_data) : configuration(
            std::move(configuration_data)) {}

};

enum class ConfigurationSource
{
    STDIN, FILE
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
};



#endif //OMG_CPP_OMG_CONFIG_H
