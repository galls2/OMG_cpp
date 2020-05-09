#pragma  once

//
// Created by galls2 on 18/09/19.
//

#include <utility>
#include <string>
#include <vector>
#include <array>
#include <utils/omg_utils.h>

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

    static constexpr std::array<char, 2> s_terminating_signs{make_array(' ',')')};
    static constexpr std::array<char, 2> s_negation_signs{make_array('!', '~')};
    static constexpr std::array<char, 2> s_brackets{make_array('(', ')')};
    static constexpr std::array<char, 8> s_temporal{make_array('A', 'E', 'F', 'G', 'U', 'W', 'R', 'X')};
    static constexpr std::array<char, 3> s_spaces{make_array(' ', '\t', '\n')};
private:
    std::string _data;
    bool _is_ap;
    std::string _token_type;
};

class Lexer {
public:
    std::vector<Token> lex(const std::string& input) const;

};

template<size_t N>
bool in_collection(char look_for, const std::array<char, N>& chars)
{
    for (const auto inside : chars) { if (inside == look_for) return true; }
    return false;
}