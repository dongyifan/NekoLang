//
//  lexer.cpp
//  NekoLang
//
//  Created by YIFAN DONG on 2022/6/25.
//

#include "lexer.hpp"
#include "token.hpp"
namespace NekoLang {

bool IsLetter(char ch) {
    return ('a' <= ch && ch <= 'z') || ('A' <= ch && ch <= 'Z') || (ch == '_');
}

bool IsDigit(char ch) {
    return '0' <= ch && ch <= '9';
}

Lexer::Lexer(const std::string& input) : input_{input} {
    ReadChar();
}

void Lexer::ReadChar() {
    if (readPosition_ >= input_.length()) {
        ch_ = 0;
    } else {
        ch_ = input_[readPosition_];
    }
    position_ = readPosition_;
    readPosition_ += 1;
}

char Lexer::PeekChar() {
    if (readPosition_ >= input_.length()) {
        return 0;
    } else {
        return input_[readPosition_];
    }
}

Token Lexer::NextToken() {
    Token token;
    
    SkipWhiteSpace();
    
    switch (ch_) {
        case '=':
            if (PeekChar() == '=') {
                char ch = ch_;
                ReadChar();
                token.literal.push_back(ch);
                token.literal.push_back(ch_);
                token.type = EQ;
            } else {
                token.type = ASSIGN;
                token.literal.push_back(ch_);
            }
            break;
        case '+':
            token.type = PLUS;
            token.literal.push_back(ch_);
            break;
        case '-':
            token.type = MINUS;
            token.literal.push_back(ch_);
            break;
        case '!':
            if (PeekChar() == '=') {
                char ch = ch_;
                ReadChar();
                token.literal.push_back(ch);
                token.literal.push_back(ch_);
                token.type = NOT_EQ;
            } else {
                token.type = BANG;
                token.literal.push_back(ch_);
            }
            break;
        case '/':
            token.type = SLASH;
            token.literal.push_back(ch_);
            break;
        case '*':
            token.type = ASTERISK;
            token.literal.push_back(ch_);
            break;
        case '<':
            token.type = LT;
            token.literal.push_back(ch_);
            break;
        case '>':
            token.type = GT;
            token.literal.push_back(ch_);
            break;
        case ';':
            token.type = SEMICOLON;
            token.literal.push_back(ch_);
            break;
        case '(':
            token.type = LPAREN;
            token.literal.push_back(ch_);
            break;
        case ')':
            token.type = RPAREN;
            token.literal.push_back(ch_);
            break;
        case ',':
            token.type = COMMA;
            token.literal.push_back(ch_);
            break;
        case '{':
            token.type = LBRACE;
            token.literal.push_back(ch_);
            break;
        case '}':
            token.type = RBRACE;
            token.literal.push_back(ch_);
            break;
        case 0:
            token.type = THEEOF;
            token.literal = "eof";
            break;
        default:
            if (IsLetter(ch_)) {
                token.literal = ReadIdentifier();
                token.type = LookupIdent(token.literal);
                return token;
            } else if (IsDigit(ch_)) {
                token.type = INT;
                token.literal = ReadNumber();
                return token;
            } else {
                token.type = ILLEGAL;
                token.literal.push_back(ch_);
            }
            break;
    }
    ReadChar();
    return token;
}

std::string Lexer::ReadIdentifier() {
    int position = position_;
    while (IsLetter(ch_)) {
        ReadChar();
    }
    std::string id = input_.substr(position, position_ - position);
    return id;
}

std::string Lexer::ReadNumber() {
    int position = position_;
    while (IsDigit(ch_)) {
        ReadChar();
    }
    return input_.substr(position, position_ - position);
}

void Lexer::SkipWhiteSpace() {
    while (ch_ == ' ' || ch_ == '\t' || ch_ == '\n' || ch_ == '\r') {
        ReadChar();
    }
}

}
