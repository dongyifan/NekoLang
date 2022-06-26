//
//  repl.cpp
//  NekoLang
//
//  Created by YIFAN DONG on 2022/6/26.
//

#include "repl.hpp"
#include <string>

#include "token.hpp"
#include "lexer.hpp"

namespace NekoLang {

void ReplStart(std::istream& in, std::ostream& out) {
    std::string line;
    while (true) {
        out << ">> ";
        if (!std::getline(in, line)) {
            return;
        }
        
        Lexer lexer(line);
        
        Token token;
        do {
            token = lexer.NextToken();
            out << token << "\n";
        } while (token.type.compare(THEEOF) != 0);
    }
}

}
