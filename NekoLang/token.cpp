//
//  token.cpp
//  NekoLang
//
//  Created by YIFAN DONG on 2022/6/25.
//

#include "token.hpp"
#include <iostream>

namespace NekoLang {

namespace {
const std::map<std::string_view, std::string_view> KeyWords = {
    {"fn", FUNCTION},
    {"let", LET},
    {"true", TRUE_KEY},
    {"false", FALSE_KEY},
    {"if", IF},
    {"else", ELSE},
    {"return", RETURN}
};
}

std::ostream& operator<<(std::ostream& os, const Token& token) {
    os << token.type << " " << token.literal;
    return os;
}

TokenType LookupIdent(std::string_view ident) {
    if (KeyWords.contains(ident)) {
        return KeyWords.at(ident);
    }
    return IDENT;
}

}
