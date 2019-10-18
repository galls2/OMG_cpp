//
// Created by galls2 on 29/09/19.
//

#include <fstream>
#include <utils/string_utils.h>
#include <map>
#include <boost/variant.hpp>
#include "omg_config.h"

std::unordered_map<std::string, ValueType> OmgConfigurationBuilder::configuration_fields =
        {
                {"Properties per specification", ValueType::BOOLEAN},
                {"Brother Unification",          ValueType::BOOLEAN},
                {"Trivial Split Elimination",    ValueType::BOOLEAN},
                {"Sat Solver",                   ValueType::STRING}
        };


OmgConfiguration OmgConfigurationBuilder::build() {
    switch (_config_src) {
        case ConfigurationSource::FILE: {
            return get_config_from_file();
        }
        case ConfigurationSource::STDIN: {
            throw OmgConfigurationException("Unsupported configuration input option.");
        }
        case ConfigurationSource::DEFAULT: {
                    ConfigTable config_table = {
                            {"Properties per specification", true},
                            {"Brother Unification", true},
                            {"Trivial Split Elimination", true},
                            {"Sat Solver", "z3"}
                    };
            return OmgConfiguration(config_table);
        }
        default: {
            throw OmgConfigurationException("Unsupported configuration input option.");
        }
    }
}

OmgConfiguration OmgConfigurationBuilder::get_config_from_file() const {

    ConfigTable config_data;
    size_t properties_found_counter = 0;

    std::ifstream infile(_config_file_path.c_str());

    std::string line;
    while (getline(infile, line)) {
        std::array<std::string, 2> parts = split_to<2>(line, ':');
        if (configuration_fields.find(parts[0]) != configuration_fields.end()) {
            ++properties_found_counter;
            switch (configuration_fields[parts[0]]) {
                case ValueType::BOOLEAN: {
                    if (parts[1] == "True") config_data[parts[0]] = true;
                    if (parts[1] == "False") config_data[parts[0]] = false;
                    throw OmgConfigurationException(
                            std::string("Illegal boolean value ").append(parts[0]).append(
                                    ". Must be True/False").data());
                    break;
                }
                case ValueType::NUMERIC: {
                    try {
                        config_data[parts[0]] = stoi(parts[1]);
                    }
                    catch (std::exception &ex) // Should be std::invalid_argument OR std::out_of_range
                    {
                        throw OmgConfigurationException(
                                std::string("Illegal integer value ").append(parts[1]).append(":")
                                        .append(ex.what()).data());
                    }
                    break;
                }
                case ValueType::STRING:
                    config_data[parts[0]] = parts[1];
                    break;
                default:
                    throw OmgConfigurationException("Unknown value type.");
            }
        } else
            throw OmgConfigurationException((std::string("Unrecognized configuration ").append(parts[0])).data());
    }
    if (properties_found_counter < configuration_fields.size())
                throw OmgConfigurationException("Not enough properties in configuration");
    return OmgConfiguration(config_data);
}



