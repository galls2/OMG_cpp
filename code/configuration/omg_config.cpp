//
// Created by galls2 on 29/09/19.
//

#include <fstream>
#include <utils/omg_exception.h>
#include <utils/string_utils.h>
#include "omg_config.h"

std::unordered_map<std::string, ValueType> OmgConfigurationBuilder::configuration_fields =
        {
                {"Properties per specification", ValueType::BOOLEAN }
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
