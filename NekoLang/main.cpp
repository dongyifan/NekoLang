//
//  main.cpp
//  NekoLang
//
//  Created by YIFAN DONG on 2022/6/25.
//

#ifdef __cpp_modules
import std;
import "lexer.hpp";
import "repl.hpp";
#else
#include <iostream>
#include <type_traits>
#include <vector>
#endif;

using namespace nekolang;
//#include "token.hpp"
//#include "lexer.hpp"
//#include "repl.hpp"
//
//using namespace NekoLang;

void Test_Lexer_Simple() 
{
    Lexer lexer("=+(){},");
    Token token;
    do {
        token = lexer.next_token();
        std::cout << token.type << ": " << token.literal << "\n";
    } while (token.type != EOF_);
}

void Test_Next_Token()
{
    static constexpr const char* code = R"(
let five = 5;
let ten = 10;

let add = fn(x, y) {
    x + y;
};

let result = add(five, ten);
)";
    Lexer lexer(code);
    Token token;
    do {
        token = lexer.next_token();
        std::cout << token.type << ": " << token.literal << "\n";
    } while (token.type != EOF_);
}
//
void Test_Lexer_With_Ident_And_Keyword() {
    static constexpr const char* code =R"(let five = 5;
let ten = 10;

let add = fn(x, y) {
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
        token = lexer.next_token();
        std::cout << token << "\n";
    } while (token.type != EOF_);
}

int main(int argc, const char * argv[]) {
//    TestLexerWithIdentAndKeyword();
    
    //std::cout << "Hello! This is the Neko programming language!\n";
    //std::cout << "Feel free to type in commands\n";
    //
    //ReplStart(std::cin, std::cout);

    //std::string input = "=+(){},;";
    //Lexer lexer{ input };
    //
    //for (Token token = lexer.next_token(); token.type != EOF_; token = lexer.next_token())
    //{
    //    std::cout << token.type << ": " << token.literal << '\n';
    //}

    //Test_Next_Token();
    //Test_Lexer_With_Ident_And_Keyword();

    repl_start(std::cin, std::cout);

    std::cout << "Hello World!";
    
    return 0;
}

