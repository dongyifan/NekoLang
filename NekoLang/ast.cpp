//
//  ast.cpp
//  NekoLang
//
//  Created by YIFAN DONG on 2022/7/2.
//

#include "ast.hpp"

namespace NekoLang {

std::string Program::TokenLiteral() {
    if (statements_.size() > 0) {
        return statements_[0]->TokenLiteral();
    } else {
        return "";
    }
}



std::string Identifier::TokenLiteral() {
    return token_.literal;
}

void Identifier::ExpressionNode() {
    
}

std::string LetStatement::TokenLiteral() {
    return token_.literal;
}
void LetStatement::StatementNode() {
    
}

}
