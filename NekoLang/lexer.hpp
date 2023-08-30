#ifndef neko_lang_hpp_
#define neko_lang_hpp_
#include <string>
#include <string_view>
#include <stdexcept>

namespace nekolan {

inline constexpr std::string_view ILLEGAL = "ILLEGAL";
inline constexpr std::string_view EOF_ = "EOF";
inline constexpr std::string_view IDENT = "IDENT";
inline constexpr std::string_view INT = "INT";
inline constexpr std::string_view ASSIGN = "=";
inline constexpr std::string_view PLUS = "+";
inline constexpr std::string_view COMMA = ",";
inline constexpr std::string_view SEMICOLON = ";";
inline constexpr std::string_view LPAREN = "(";
inline constexpr std::string_view RPAREN = ")";
inline constexpr std::string_view LBRACE = "{";
inline constexpr std::string_view RBRACE = "}";
inline constexpr std::string_view FUNCTION = "FUNCTION";
inline constexpr std::string_view LET = "LET";


struct Token
{
	std::string_view type;
	std::string_view literal;
};

class Lexer
{
private:
	std::string_view input_;
	int position_ = 0;
	int readPosition_ = 0;
	char ch_ = 0;

public:
	Lexer(const std::string& input) : input_{input}
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

	Token next_token() 
	{
		Token token;

		switch (ch_)
		{
		case '=':
			token = { ASSIGN, input_.substr(position_, 1) };
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
			throw std::logic_error{ "next_token shouldn't come to default branch" };
			break;
		}
		read_char();
		return token;
	}
};

}

#endif // !neko_lang_hpp_

