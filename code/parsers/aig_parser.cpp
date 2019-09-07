//
// Created by galls2 on 07/09/19.
//

#include "aig_parser.h"
#include "../utils/aiger-1.9.9/aiger.h
AigParser::AigParser(const std::string &aig_path)
{

}

const std::map<AigMetadata, size_t> &AigParser::get_aig_metadata()
{
    return _aig_metadata;
}



