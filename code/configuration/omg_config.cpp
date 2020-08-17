//
// Created by galls2 on 29/09/19.
//

#include <fstream>
#include <utils/string_utils.h>
#include <map>
#include <boost/variant.hpp>
#include "omg_config.h"

std::unordered_map<std::string, ValueType> OmgConfigBuilder::configuration_fields =
        {
                {"Properties per specification", ValueType::BOOLEAN},
                {"Brother Unification",          ValueType::BOOLEAN},
                {"Trivial Split Elimination",    ValueType::BOOLEAN},
                {"Sat Solver",                   ValueType::STRING},
                {"Epr Solver",                   ValueType::STRING},
                {"Timeout",                   ValueType::NUMERIC}

        };


void OmgConfigBuilder::build() {
    switch (_config_src) {
        case ConfigurationSource::FILE: {
            ConfigTable config_table = get_config_from_file();
            OmgConfig::load_config_table(config_table);
            break;
        }
        case ConfigurationSource::STDIN: {
            throw OmgConfigException("Unsupported configuration input option.");
        }
        case ConfigurationSource::DEFAULT: {
                    ConfigTable config_table = {
                            {"Properties per specification", false},
                            {"Brother Unification", true},
                            {"Trivial Split Elimination", true},
                            {"Timeout", 60},
                            {"Sat Solver", std::string("bdd")},
                            {"Epr Solver", std::string("z3")}
                    };
            OmgConfig::load_config_table(config_table);
            break;
        }
        default: {
            throw OmgConfigException("Unsupported configuration input option.");
        }
    }
}

ConfigTable OmgConfigBuilder::get_config_from_file() const {

    ConfigTable config_data;
    size_t properties_found_counter = 0;

    std::ifstream infile(_config_file_path.c_str());

    std::string line;
    while (getline(infile, line)) {
        if (line.length() == 0) continue;
        std::array<std::string, 2> parts = split_to<2>(line, ':');
        if (configuration_fields.find(parts[0]) != configuration_fields.end()) {
            ++properties_found_counter;
            switch (configuration_fields[parts[0]]) {
                case ValueType::BOOLEAN: {
                    if (parts[1] == "True") config_data[parts[0]] = true;
                    else if (parts[1] == "False") config_data[parts[0]] = false;
                    else throw OmgConfigException(
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
                        throw OmgConfigException(
                                std::string("Illegal integer value ").append(parts[1]).append(":")
                                        .append(ex.what()).data());
                    }
                    break;
                }
                case ValueType::STRING:
                    config_data[parts[0]] = parts[1];
                    break;
                default:
                    throw OmgConfigException("Unknown value type.");
            }
        } else
            throw OmgConfigException((std::string("Unrecognized configuration ").append(parts[0])).data());
    }
    if (properties_found_counter < configuration_fields.size())
                throw OmgConfigException("Not enough properties in configuration");
    return config_data;
}


ConfigTable OmgConfig::_configuration = {};

std::string OmgConfig::config_table_to_string() {
    std::string to_return;
    for (const auto& it : _configuration)
    {

        to_return += it.first + " : ";
        if (OmgConfigBuilder::configuration_fields[it.first] == ValueType::STRING)
            to_return += boost::get<std::string>(it.second);
        else if (OmgConfigBuilder::configuration_fields[it.first] == ValueType::NUMERIC)
            to_return += std::to_string(boost::get<int>(it.second));
        else
            to_return += boost::get<bool>(it.second) ? "True" : "False";

        to_return += '\n';
    }
    return to_return;
}
