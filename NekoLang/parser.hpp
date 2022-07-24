//
//  parser.hpp
//  NekoLang
//
//  Created by YIFAN DONG on 2022/7/2.
//

#ifndef parser_hpp
#define parser_hpp

#include "token.hpp"
#include "lexer.hpp"
#include "ast.hpp"

namespace NekoLang {

class Parser {
public:
    Parser(const Lexer& lexer);
    Program* ParserProgram() {return nullptr;}
private:
    void NextToken();
private:
    Lexer lexer_;
    Token curToken_;
    Token peekToken_;
};

}

#endif /* parser_hpp */
