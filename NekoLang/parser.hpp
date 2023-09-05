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
	Parser() 
	{
		next_token();
		next_token();
	}

	Program* parse_pargram()
	{
		Program* program = new Program();
		return nullptr;
	}

	void next_token()
	{
		curToken_ = peekToken_;
		peekToken_ = lexer_->next_token();
	}

private:
	Lexer* lexer_;
	Token curToken_;
	Token peekToken_;
};

}
#endif // !neko_lang_parser_hpp

