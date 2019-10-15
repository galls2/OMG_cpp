//
// Created by galls2 on 29/09/19.
//

#include <fstream>
#include <utils/string_utils.h>
#include "omg_config.h"

std::unordered_map<std::string, ValueType> OmgConfigurationBuilder::configuration_fields =
        {
                {"Properties per specification", ValueType::BOOLEAN},
                {"Brother Unification", ValueType::BOOLEAN},
                {"Trivial Split Elimination", ValueType::BOOLEAN},

                {"Sat Solver", ValueType::STRING}

        };


OmgConfiguration OmgConfigurationBuilder::build() {

    std::unordered_map<std::string, std::string> config_data;
    size_t properties_found_counter = 0;

    switch (_config_src) {
        case ConfigurationSource::FILE: {
            std::ifstream infile(_config_file_path.c_str());

            std::string line;
            while (std::getline(infile, line))
            {
                std::array<std::string, 2> parts = split_to<2>(line, ':');
                if (configuration_fields.find(parts[0]) != configuration_fields.end())
                {
                    ++properties_found_counter;
                    config_data[parts[0]] = parts[1];
                }
                else
                    throw OmgConfigurationException((std::string("Unrecognized configuration ")+std::string(parts[0])).data());
            }
            if (properties_found_counter < configuration_fields.size())
                throw OmgConfigurationException("Not enough properties in configuration");
            break;

        }
        case ConfigurationSource::STDIN: {
            throw OmgConfigurationException("Unsupported configuration input option.");
            break;
        }
        default: {
            throw OmgConfigurationException("Unsupported configuration input option.");
            break;
        }
    }



}


const std::string &OmgConfiguration::get_string_value(const std::string &key) const {
    if (_configuration.find(key) == _configuration.end())
        throw OmgConfigurationException(std::string("Unrecognized configuration ").append(key).data());
    const std::string& val = _configuration.at(key);
    return val;
}

bool OmgConfiguration::get_bool_value(const std::string &key) const {
    const std::string &val = get_string_value(key);
    if (val == "True") return true;
    if (val == "False") return false;
    throw OmgConfigurationException(std::string("Illegal boolean value ").append(val).append(". Must be True/False").data());
}

int OmgConfiguration::get_integer_value(const std::string &key) const {
    const std::string &val = get_string_value(key);
    try
    {
        return std::stoi(val);
    }
    catch (std::exception& ex) // Should be std::invalid_argument OR std::out_of_range
    {
        throw OmgConfigurationException(std::string("Illegal integer value ").append(val).append(":")
        .append(ex.what()).data());
    }
}

