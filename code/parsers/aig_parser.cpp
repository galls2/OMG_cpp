//
// Created by galls2 on 07/09/19.
//
#include <fstream>
#include <vector>
#include <iostream>
#include <cassert>

#include "../utils/aiger-1.9.9/aiger.h"
#include "../utils/string_utils.h"

#include "aig_parser.h"


AigParser::AigParser(const std::string &aig_path) : _aig_path(aig_path)
{
  _aag_path = aig_to_aag(aig_path);

  std::vector<std::string> file_lines;
  read_aag(file_lines);
  extract_metadata(file_lines[0]);
  std::cout << _aig_metadata[AigMetadata::M] << " " << _aig_metadata[AigMetadata::I]<< std::endl;
}

std::string AigParser::aig_to_aag(const std::string& aig_path) // change someday to something less disgusting
{
  std::string PATH_TO_EXE = "/home/galls2/Desktop/OMG_cpp/code/utils/aiger-1.9.9/aigtoaig";
  std::string out_path = std::string(aig_path).replace(aig_path.length()-2, 1, std::string("a"));
  std::string conversion_cmd = PATH_TO_EXE + " " + aig_path + " " + out_path;
  std::cout << conversion_cmd << std::endl;
  system(conversion_cmd.c_str());
  return out_path;
}

void AigParser::read_aag(std::vector<std::string>& aag_container) const
{
    std::string line;
    std::ifstream aag_file(_aag_path.c_str());
    while (std::getline(aag_file, line))
    {
      aag_container.push_back(line);
    }
}

void AigParser::extract_metadata(const std::string& first_aag_line)
{
    std::vector<std::string> components;
    split(first_aag_line, ' ', components);
    assert(components[0] == std::string("aag"));
    _aig_metadata[AigMetadata::M] = std::stoul(components[1]);
    _aig_metadata[AigMetadata::I] = std::stoul(components[2]);
    _aig_metadata[AigMetadata::L] = std::stoul(components[3]);
    _aig_metadata[AigMetadata::O] = std::stoul(components[4]);
    _aig_metadata[AigMetadata::A] = std::stoul(components[5]);
}



const std::map<AigMetadata, size_t> &AigParser::get_aig_metadata()
{
    return _aig_metadata;
}
