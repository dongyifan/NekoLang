//
//  parser.cpp
//  NekoLang
//
//  Created by YIFAN DONG on 2022/7/2.
//

#include "parser.hpp"

namespace NekoLang {

Parser::Parser(const Lexer& lexer) : lexer_(lexer) {
    NextToken();
    NextToken();
}

void Parser::NextToken() {
    curToken_ = peekToken_;
    peekToken_ = lexer_.NextToken();
}

}
