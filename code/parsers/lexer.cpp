//
// Created by galls2 on 18/09/19.
//

#include "lexer.h"

bool in_collection(char look_for, std::vector<char> chars)
{
    for (const auto inside : chars) { if (inside == look_for) return true; }
    return false;
}

std::vector<Token> Lexer::lex(const std::string &input) const {
    std::vector<Token> tokens;
    size_t index = 0;
    while (index < input.length())
    {
        if (input[index] == ' ') { ++index; continue; }
        if (in_collection(input[index], {'(', ')', '|', '~', '!', '&', 'A', 'E', 'F', 'G', 'U', 'W', 'R', 'V', 'X'}))
        {
            tokens.emplace_back(input[index++]);
            continue;
        }

        if (input[index] == '-' && input[index+1] == '>')
        {
            tokens.emplace_back(Token("->"));
            index += 2;
            continue;
        }

        size_t count_to_delim = 0;
        while (!in_collection(input[index+count_to_delim], {' ', ')'}))
        {
            ++count_to_delim;
        }

        Token atomic_token(input.substr(index, count_to_delim));
        tokens.emplace_back(atomic_token);
        index += count_to_delim;

    }
    return tokens;
}

std::ostream &operator<<(std::ostream &os, const Token& token)
{
    os << token.get_data();
    return os;
}
