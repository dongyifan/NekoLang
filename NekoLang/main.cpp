//
//  main.cpp
//  NekoLang
//
//  Created by YIFAN DONG on 2022/6/25.
//

#include <iostream>
#include <type_traits>
#include "token.hpp"
#include "lexer.hpp"
#include "repl.hpp"

using namespace NekoLang;
void TestLexerSimple() {
    Lexer lexer("=+(){},");
    Token token;
    do {
        token = lexer.NextToken();
        std::cout << token << "\n";
    } while (token.type.compare(THEEOF) != 0);
}

void TestLexerWithIdentAndKeyword() {
    static constexpr const char* code =R"(let five = 5;
let ten = 10;

let add = func(x, y) {
    x + y;
};

let result = add(five, ten);
!-/*5;
5 < 10 > 5;

if (5 < 10) {
    return true;
} else {
    return false;
}

10 == 10;
10 != 9;
)";
    Lexer lexer(code);
    Token token;
    do {
        token = lexer.NextToken();
        std::cout << token << "\n";
    } while (token.type.compare(THEEOF) != 0);
}

int main(int argc, const char * argv[]) {
//    TestLexerWithIdentAndKeyword();
    
    std::cout << "Hello! This is the Neko programming language!\n";
    std::cout << "Feel free to type in commands\n";
    
    ReplStart(std::cin, std::cout);
    
    return 0;
}

