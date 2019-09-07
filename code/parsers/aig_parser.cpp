//
// Created by galls2 on 07/09/19.
//
#include <fstream>
#include <vector>
#include <iostream>

#include "../utils/aiger-1.9.9/aiger.h
#include "../utils/string_utils.h"

#include "aig_parser.h"


AigParser::AigParser(const std::string &aig_path)
{
  std::string out_path = aig_to_aag(aig_path);

  std::vector<std::string> file_lines;
  read_aag(out_path, file_lines);
  extract_metadata(file_lines[0]);
  std::cout << _aig_metadata[AigMetadata::M] << std::endl;
}

std::string AigParser::aig_to_aag(const std::string& aig_path) // change someday to something less disgusting
{
  std::string PATH_TO_EXE = "\/home\/galls2\/Desktop\/OMG_cpp\/code\/utils\/aiger-1.9.9\/aigtoaig";
  std::string out_path = string(PATH_TO_EXE).replace(PATH_TO_EXE.length()-2, 1, std::string("a"));
  std::string conversion_cmd = PATH_TO_EXE + " " + aig_path + " " + out_path;
  system(conversion_cmd.c_str());
  return out_path;
}

void read_aag(const std::string& aag_path, std::vector<std::string>& aag_container)
{
  std::ifstream aag_file(out_path.c_str());
  while (std::getline(infile, line))
  {
    aag_container.push_back(line);
  }
}

void extract_metadata(const std::string& first_aag_line)
{
    std::vector<std::string> components;
    split(first_aag_line, ' ', components);
    assert(components[0] == std::string("p"))
    _aig_metadata[AigMetadata::M] = atoi(components[1]);
    _aig_metadata[AigMetadata::I] = atoi(components[2]);
    _aig_metadata[AigMetadata::L] = atoi(components[3]);
    _aig_metadata[AigMetadata::O] = atoi(components[4]);
    _aig_metadata[AigMetadata::A] = atoi(components[5]);
}



const std::map<AigMetadata, size_t> &AigParser::get_aig_metadata()
{
    return _aig_metadata;
}
