#include <utility>

//
// Created by galls2 on 18/09/19.
//

#ifndef OMG_CPP_LEXER_H
#define OMG_CPP_LEXER_H

#include <string>
#include <vector>
class Token
{
public:
    Token() : _data("") {}

    explicit Token(std::string data) : _data(std::move(data)) {}
    explicit Token(char data) : _data(std::string(1, data)) {}
    std::string get_data() const { return _data; }
    friend bool operator<(const Token& l, const Token& r)
    {
        return l < r;
    }
    friend std::ostream& operator<<(std::ostream& os, const Token& token);
private:
    std::string _data;
};

class Lexer {
public:
    std::vector<Token> lex(const std::string& input) const;

};


#endif //OMG_CPP_LEXER_H
