//
// Created by galls2 on 07/09/19.
//

#ifndef OMG_CPP_AIG_PARSER_H
#define OMG_CPP_AIG_PARSER_H

#include <map>
#include <vector>
#include <string>
#include <z3++.h>

enum AigMetadata{
    M = 0, I = 1, L = 2, O = 3, A = 4
};



class AigParser {
public:

    explicit AigParser(const std::string& aig_path);
    const std::map<AigMetadata, size_t>& get_aig_metadata();
    ~AigParser() = default;



private:
    std::string aig_to_aag(const std::string& aig_path0);
    void read_aag(std::vector<std::string>& aag_container) const;
    void extract_metadata(const std::string& first_aag_line);

    const std::string _aig_path;
    std::string _aag_path;

    std::map<AigMetadata, size_t> _aig_metadata;
    std::map<std::string, std::string> _ap_to_symb;
    std::map<std::string, std::string> _symb_to_ap;

    void extract_ap_mapping(const std::vector<std::string>& vector);

    std::map<size_t, z3::expr> get_literal_formulas(const std::vector<std::string>& aag_lines);
};


#endif //OMG_CPP_AIG_PARSER_H
