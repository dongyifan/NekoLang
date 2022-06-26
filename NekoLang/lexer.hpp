//
//  lexer.hpp
//  NekoLang
//
//  Created by YIFAN DONG on 2022/6/25.
//

#ifndef lexer_hpp
#define lexer_hpp
#include <string>

namespace NekoLang {

struct Token;

class Lexer {
public:
    Lexer(const std::string& input);
    
    Token NextToken();
private:
    void ReadChar();
    char PeekChar();
    std::string ReadIdentifier();
    std::string ReadNumber();
    void SkipWhiteSpace();
    
    std::string input_;
    int position_ = 0;
    int readPosition_ = 0;
    char ch_ = 0;
};

}

#endif /* lexer_hpp */
