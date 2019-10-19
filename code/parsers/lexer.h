#pragma  once

//
// Created by galls2 on 18/09/19.
//

#include <utility>
#include <string>
#include <vector>
class Token
{
public:
    Token() : _data("ERROR"), _is_ap(false), _token_type("ERROR") {}
    explicit Token(std::string data, bool is_ap=false) : _data(std::move(data)), _is_ap(is_ap), _token_type(is_ap ? "AP" : _data) { }
    explicit Token(char data, bool is_ap=false) : _data(std::string(1, data)), _is_ap(is_ap), _token_type(is_ap ? "AP" : _data) {}
    std::string get_data() const { return _data; }
    bool is_ap() const { return _is_ap; }
    Token get_token_type() const { return Token(_token_type); }

    friend bool operator<(const Token& l, const Token& r)
    {
        return l.get_data() < r.get_data();
    }
    friend std::ostream& operator<<(std::ostream& os, const Token& token);
private:
    std::string _data;
    bool _is_ap;
    std::string _token_type;
};

class Lexer {
public:
    std::vector<Token> lex(const std::string& input) const;

};
