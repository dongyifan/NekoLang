//
//  token.hpp
//  NekoLang
//
//  Created by YIFAN DONG on 2022/6/25.
//

#ifndef token_hpp
#define token_hpp

#include <string_view>
#include <string>
#include <iostream>
#include <map>

namespace NekoLang {

using TokenType = std::string_view;

inline constexpr std::string_view ILLEGAL = "ILLEGAL";
inline constexpr std::string_view THEEOF = "EOF";

inline constexpr std::string_view IDENT = "IDENT"; // add, foobar, x,
inline constexpr std::string_view INT = "INT";

inline constexpr std::string_view ASSIGN = "=";
inline constexpr std::string_view PLUS = "+";
inline constexpr std::string_view MINUS = "-";
inline constexpr std::string_view BANG = "!";
inline constexpr std::string_view ASTERISK = "*";
inline constexpr std::string_view SLASH = "/";

inline constexpr std::string_view LT = "<";
inline constexpr std::string_view GT = ">";
inline constexpr std::string_view EQ = "==";
inline constexpr std::string_view NOT_EQ = "!=";

inline constexpr std::string_view COMMA = ",";
inline constexpr std::string_view SEMICOLON = ";";

inline constexpr std::string_view LPAREN = "(";
inline constexpr std::string_view RPAREN = ")";
inline constexpr std::string_view LBRACE = "{";
inline constexpr std::string_view RBRACE = "}";

inline constexpr std::string_view FUNCTION = "FUNCTION";
inline constexpr std::string_view LET = "LET";
inline constexpr std::string_view TRUE_KEY = "TRUE";
inline constexpr std::string_view FALSE_KEY = "FALSE";
inline constexpr std::string_view IF = "IF";
inline constexpr std::string_view ELSE = "ELSE";
inline constexpr std::string_view RETURN = "RETURN";



struct Token {
    TokenType type;
    std::string literal;
};

std::ostream& operator<<(std::ostream& os, const Token& token);

TokenType LookupIdent(std::string_view ident);

}

#endif /* token_hpp */
