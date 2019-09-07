//
// Created by galls2 on 07/09/19.
//

#ifndef OMG_CPP_AIG_PARSER_H
#define OMG_CPP_AIG_PARSER_H

#include <map>
#include <string>

enum AigMetadata{
    M = 0, I = 1, L = 2, O = 3, A = 4
};


class AigParser {
public:

    explicit AigParser(const std::string& aig_path);
    const std::map<AigMetadata, size_t>& get_aig_metadata();




private:
    std::string _aig_path;
    std::map<AigMetadata, size_t> _aig_metadata;
};


#endif //OMG_CPP_AIG_PARSER_H
