#ifndef neko_lang_repl_hpp
#define neko_lang_repl_hpp

#ifdef __cpp_modules
import std;
#else
#include <iostream>
#endif // __cpp_modules

#include "lexer.hpp"

namespace nekolang {
inline constexpr const char* PROMOPT = ">> ";

void repl_start(std::istream& in, std::ostream& out)
{
	std::string line;
	while (true) {
		out << PROMOPT;
		if (!std::getline(in, line)) {
			return;
		}

		Lexer lexer{ line };
		Token token;
		do {
			token = lexer.next_token();
			out << token << '\n';
		} while (token.type != EOF_);
	}
}

}


#endif // !neko_lang_repl_hpp

