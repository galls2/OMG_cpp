//
// Created by galls2 on 18/09/19.
//

#include "lexer.h"

constexpr std::array<char, 2> Token::s_terminating_signs;
constexpr std::array<char, 2> Token::s_negation_signs;
constexpr std::array<char, 8> Token::s_temporal;
constexpr std::array<char, 2> Token::s_brackets;
constexpr std::array<char, 3> Token::s_spaces;

std::vector<Token> Lexer::lex(const std::string &input) const {
    std::vector<Token> tokens;
    size_t index = 0;
    while (index < input.length())
    {
        if (input[index] == ' ') { ++index; continue; }
        if (in_collection(input[index], Token::s_brackets) ||  // (in_collection(input[index], Token::s_temporal)))
            (in_collection(input[index], Token::s_temporal) && (index + 1) < input.length() &&
                    (in_collection(input[index+1], Token::s_spaces ) || in_collection(input[index+1], Token::s_temporal) ||
                    in_collection(input[index+1], Token::s_negation_signs)  || in_collection(input[index+1], Token::s_brackets
                    )  )))
        {
            tokens.emplace_back(input[index++]);
            continue;
        }
        if (input[index] == '|')
        {
            ++index;
            tokens.emplace_back("OR");
            continue;
        }
        if (input[index] == '&')
        {
            ++index;
            tokens.emplace_back("AND");
            continue;
        }
        if (in_collection(input[index], Token::s_negation_signs))
        {
            ++index;
            tokens.emplace_back("NOT");
            continue;
        }
        if (input[index] == '^')
        {
            ++index;
            tokens.emplace_back("XOR");
            continue;
        }

        if (input.compare(index, 2, "->") == 0)
        {
            tokens.emplace_back("ARROW");
            index += 2;
            continue;
        }

        if (input.compare(index, 2, "==") == 0)
        {
            tokens.emplace_back("EQUIV");
            index += 2;
            continue;
        }

        size_t count_to_delim = 0;
        while ((index + count_to_delim) < input.length() && !in_collection(input[index+count_to_delim], Token::s_terminating_signs))
        {
            ++count_to_delim;
        }

        tokens.emplace_back(input.substr(index, count_to_delim), true);
        index += count_to_delim;

    }
    return tokens;
}

std::ostream &operator<<(std::ostream &os, const Token& token)
{
    os << token.get_data();
    return os;
}
