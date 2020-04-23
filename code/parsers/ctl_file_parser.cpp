//
// Created by galls2 on 27/09/19.
//

#include "ctl_file_parser.h"
#include <fstream>
#include <iterator>
#include <sstream>
#include <regex>
#include <parsers/ctl_parser.h>
#include <parsers/ctl_parser_data.h>

bool CtlFileParser::parse_ctl_file(const std::string &file_path, std::vector<FormulaChunk> &formula_chunks) const{
    std::ifstream infile(file_path.c_str());

    RawFormulaChunk current_chunk;

    std::string line;
    while (std::getline(infile, line))
    {
      if (line.length() == 0 || line[0] == '\n') continue;

      if (line[0] == '#' && (current_chunk.empty() || current_chunk[current_chunk.size() - 1][0] != '#'))
      {
          if (!current_chunk.empty())
          {
              FormulaChunk formula_chunk = parse_raw_formula_chunk(current_chunk);
              formula_chunks.emplace_back(std::move(formula_chunk));
              current_chunk.clear();
          }
          current_chunk.push_back(line);
      }
      else
      {
          current_chunk.push_back(line);
      }
    }

    if (!current_chunk.empty())
    {
        FormulaChunk formula_chunk = parse_raw_formula_chunk(current_chunk);
        formula_chunks.emplace_back(std::move(formula_chunk));
    }
    return true;
}

FormulaChunk CtlFileParser::parse_raw_formula_chunk(const CtlFileParser::RawFormulaChunk &raw_formula_chunk) const
{
    bool expected_result = raw_formula_chunk[0].find(std::string("PASS")) != std::string::npos;
    FormulaChunk formula_chunk(expected_result);

    Lexer lexer;
    LR1CtlParser parser(CtlParserData::grammar_ctl, ActionTable(CtlParserData::action_table_ctl_parser), GotoTable(CtlParserData::goto_table_ctl_parser));

    bool is_multiple_properties = std::regex_search(raw_formula_chunk[0], std::regex("\\(.*-.*\\)"));

    size_t first_non_comment_line = 0;
    while (raw_formula_chunk[first_non_comment_line][0] == '#') ++first_non_comment_line;

    if (!is_multiple_properties)
    {
        std::string raw_formula;
        for (size_t line_index = first_non_comment_line; line_index < raw_formula_chunk.size(); ++line_index)
        {
            raw_formula.append(raw_formula_chunk[line_index]);
        }

        auto lex_result = lexer.lex(raw_formula);
        auto parse_result = parser.parse(lex_result);
        formula_chunk.add_formula(std::move(parse_result));
    } else
    {
        // may be changed in the furute, if necessary. we assume that in a multi-formula chunk, each formula takes exactly one line
        for (size_t line_index = first_non_comment_line; line_index < raw_formula_chunk.size(); ++line_index)
        {
            const std::string& raw_formula = raw_formula_chunk[line_index];
            auto lex_result = lexer.lex(raw_formula);
            auto parse_result = parser.parse(lex_result);
            formula_chunk.add_formula(std::move(parse_result));
        }
    }
    return formula_chunk;


}
