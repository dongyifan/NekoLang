#ifndef neko_lang_parser_hpp
#define neko_lang_parser_hpp

#ifdef __cpp_modules
import std;
import "ast.hpp";
#else

#endif // __cpp_modules
namespace nekolang {

class Parser
{
public:
	Parser(std::string_view input) : lexer_{input}
	{
		next_token();
		next_token();
	}

	std::unique_ptr<Program> parse_program()
	{
		std::unique_ptr<Program> program{ new Program() };

		while (!current_token_is(EOF_))
		{
			std::unique_ptr<Statement> statement = parse_statement();
			if (statement) {
				program->add_statement(std::move(statement));
			}
			next_token();
		}
		return program;
	}

	std::unique_ptr<Statement> parse_statement()
	{
		if (curToken_.type == LET) {
			return parse_let_statement();
		}

		return nullptr;
	}

	std::unique_ptr<Statement> parse_let_statement()
	{
		std::unique_ptr<LetStatement> p = std::make_unique<LetStatement>(curToken_);
		if (!expect_peek(IDENT)) {
			return nullptr;
		}
		p->set_name(std::make_unique<Identifier>(curToken_, curToken_.literal));
		if (!expect_peek(ASSIGN)) {
			return nullptr;
		}

		while (!current_token_is(SEMICOLON) && !current_token_is(EOF_)) {
			next_token();
		}
		return p;
	}

	void next_token()
	{
		curToken_ = peekToken_;
		peekToken_ = lexer_.next_token();
	}

	bool current_token_is(TokenType type)
	{
		return curToken_.type == type;
	}

	bool peek_token_is(TokenType type)
	{
		return peekToken_.type == type;
	}

	bool expect_peek(TokenType type)
	{
		if (peek_token_is(type)) {
			next_token();
			return true;
		}
		else {
			peek_error(type);
			return false;
		}
	}

	void peek_error(TokenType type)
	{
		errors_.emplace_back(std::format("expected next token to be {}, got {} instead", type, peekToken_.type));
	}

private:
	Lexer lexer_;
	Token curToken_;
	Token peekToken_;
	std::vector<std::string> errors_;
};

}
#endif // !neko_lang_parser_hpp

