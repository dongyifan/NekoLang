#ifndef neko_lang_lexer_hpp_
#define neko_lang_lexer_hpp_

#ifdef __cpp_modules
import std;
#else
#include <string>
#include <string_view>
#include <stdexcept>
#include <map>
#endif // __cpp_modules



namespace nekolang {

inline constexpr std::string_view ILLEGAL = "ILLEGAL";
inline constexpr std::string_view EOF_ = "EOF";
inline constexpr std::string_view IDENT = "IDENT";
inline constexpr std::string_view INT = "INT";
inline constexpr std::string_view ASSIGN = "=";
inline constexpr std::string_view PLUS = "+";
inline constexpr std::string_view MINUS = "-";
inline constexpr std::string_view BANG = "!";
inline constexpr std::string_view ASTERISK = "*";
inline constexpr std::string_view SLASH = "/";
inline constexpr std::string_view LT = "<";
inline constexpr std::string_view GT = ">";
inline constexpr std::string_view EQ = "==";
inline constexpr std::string_view NOT_EQ = "!=";
inline constexpr std::string_view COMMA = ",";
inline constexpr std::string_view SEMICOLON = ";";
inline constexpr std::string_view LPAREN = "(";
inline constexpr std::string_view RPAREN = ")";
inline constexpr std::string_view LBRACE = "{";
inline constexpr std::string_view RBRACE = "}";
inline constexpr std::string_view FUNCTION = "FUNCTION";
inline constexpr std::string_view LET = "LET";
inline constexpr std::string_view TRUE_ = "TRUE";
inline constexpr std::string_view FALSE_ = "FALSE";
inline constexpr std::string_view IF = "IF";
inline constexpr std::string_view ELSE = "ELSE";
inline constexpr std::string_view RETURN = "RETURN";

inline bool is_letter(char ch)
{
    return ('a' <= ch && ch <= 'z') || ('A' <= ch && ch <= 'Z') || ch == '_';
}

inline bool is_digit(char ch)
{
    return '0' <= ch && ch <= '9';
}

using TokenType = std::string_view;

struct Token
{
    std::string_view type;
    std::string_view literal;
};

inline auto& operator<< (auto& o, const Token& t)
{
    o << t.type << ": " << t.literal;
    return o;
}

class Lexer
{
    inline static const std::map<std::string_view, TokenType> keywords = {
        {"fn", FUNCTION},
        {"let", LET},
        {"true", TRUE_},
        {"false", FALSE_},
        {"if", IF},
        {"else", ELSE},
        {"return", RETURN}
    };
private:
    std::string_view input_;
    int position_ = 0;
    int readPosition_ = 0;
    char ch_ = 0;
    
public:
    Lexer(std::string_view input) : input_{input}
    {
        read_char();
    }
    
    void read_char()
    {
        if (readPosition_ >= input_.size()) {
            ch_ = 0;
        }
        else {
            ch_ = input_[readPosition_];
        }
        position_ = readPosition_;
        readPosition_ += 1;
    }

    char peek_char()
    {
        if (readPosition_ >= input_.size()) {
            return 0;
        }
        else {
            return input_[readPosition_];
        }
    }
    
    Token next_token()
    {
        Token token;
        skip_whitespace();
        
        switch (ch_)
        {
            case '=':
                if (peek_char() == '=') {
                    int position = position_;
                    read_char();
                    token = { EQ, input_.substr(position, 2) };
                }
                else {
                    token = { ASSIGN, input_.substr(position_, 1) };
                }
                break;
            case ';':
                token = { SEMICOLON, input_.substr(position_, 1) };
                break;
            case '(':
                token = { LPAREN, input_.substr(position_, 1) };
                break;
            case ')':
                token = { RPAREN, input_.substr(position_, 1) };
                break;
            case ',':
                token = { COMMA, input_.substr(position_, 1) };
                break;
            case '+':
                token = { PLUS, input_.substr(position_, 1) };
                break;
            case '-':
                token = { MINUS, input_.substr(position_, 1) };
                break;
            case '!':
                if (peek_char() == '=') {
                    int position = position_;
                    read_char();
                    token = { NOT_EQ, input_.substr(position, 2) };
                }
                else {
                    token = { BANG, input_.substr(position_, 1) };
                }
                break;
            case '*':
                token = { ASTERISK, input_.substr(position_, 1) };
                break;
            case '/':
                token = { SLASH, input_.substr(position_, 1) };
                break;
            case '<':
                token = { LT, input_.substr(position_, 1) };
                break;
            case '>':
                token = { GT, input_.substr(position_, 1) };
                break;
            case '{':
                token = { LBRACE, input_.substr(position_, 1) };
                break;
            case '}':
                token = { RBRACE, input_.substr(position_, 1) };
                break;
            case 0:
                token = { EOF_, "" };
                break;
            default:
                if (is_letter(ch_)) {
                    token.literal = read_identifier();
                    token.type = lookup_ident(token.literal);
                    return token;
                }
                else if (is_digit(ch_)) {
                    token.type = INT;
                    token.literal = read_number();
                    return token;
                }
                else {
                    token = { ILLEGAL, input_.substr(position_, 1) };
                }
                break;
        }
        read_char();
        return token;
    }
    
    std::string_view read_identifier() 
    {
        auto position = position_;
        while (is_letter(ch_)) {
            read_char();
        }
        
        return input_.substr(position, (ptrdiff_t)position_ - position);
    }
    
    TokenType lookup_ident(std::string_view ident) 
    {
        if (keywords.contains(ident)) {
            return keywords.at(ident);
        } else {
            return IDENT;
        }
    }

    std::string_view read_number()
    {
        auto position = position_;
        while (is_digit(ch_)) {
            read_char();
        }
        return input_.substr(position, (ptrdiff_t)position_ - position);
    }

    void skip_whitespace()
    {
        while (ch_ == ' ' || ch_ == '\t' || ch_ == '\n' || ch_ == '\r') {
            read_char();
        }
    }
};

}

#endif // !neko_lang_lexer_hpp_

