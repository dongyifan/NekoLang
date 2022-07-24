//
//  ast.hpp
//  NekoLang
//
//  Created by YIFAN DONG on 2022/7/2.
//

#ifndef ast_hpp
#define ast_hpp

#include <string>
#include <vector>
#include <memory>
#include "token.hpp"

namespace NekoLang {

class Node {
public:
    virtual ~Node() = default;
    Node(const Node& other) = delete;
    Node(Node&& other) = delete;
    Node& operator=(const Node& other) = delete;
    Node& operator=(Node&& other) = delete;
    
    virtual std::string TokenLiteral() = 0;
};

class Statement : public Node {
    virtual void StatementNode() = 0;
};

class Expression: public Node {
    virtual void ExpressionNode() = 0;
};

class Program : public Node {
public:
    std::string TokenLiteral() override;
private:
    std::vector<std::unique_ptr<Statement>> statements_;
};

class Identifier : public Expression {
public:
    std::string TokenLiteral() override;
    void ExpressionNode() override;
private:
    Token token_;
    std::string value_;
};

class LetStatement : public Statement {
public:
    std::string TokenLiteral() override;
    void StatementNode()override;
private:
    Token token_;
    Identifier* name_ = nullptr;
    Expression* value;
};

}

#endif /* ast_hpp */
