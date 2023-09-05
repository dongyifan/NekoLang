#ifndef neko_lang_ast_hpp
#define neko_lang_ast_hpp

#ifdef __cpp_modules
import std;
import "lexer.hpp";
#else

#endif // __cpp_modules

namespace nekolang {

class Node
{
public:
	Node() = default;
	virtual ~Node() = default;
	virtual std::string token_literal() = 0;

	Node(const Node&) = delete;
	Node(Node&&) = delete;
	Node& operator=(const Node&) = delete;
	Node& operator=(Node&&) = delete;
};

class Statement : public Node
{
public:
	~Statement() override = default;
};

class Expression : public Node
{
public:
	~Expression() override = default;
};

class Program : public Node
{
public:
	Program() = default;
	~Program() override = default;

	std::string token_literal() override
	{
		if (statement_.size() > 0) {
			return statement_[0]->token_literal();
		}
		else {
			return "";
		}
	}
private:
	std::vector<std::unique_ptr<Statement>> statement_;
};


class Identifier : public Expression
{
public:
	~Identifier() override = default;
	std::string token_literal() override
	{
		return std::string{ token_.literal };
	}
private:
	Token token_;
	std::string value_;
};

class LetStatement : public Statement
{
public:
	~LetStatement() override = default;
	std::string token_literal() override
	{
		return std::string{ token_.literal };
	}

private:
	Token token_;
	Identifier* name_;

};

}


#endif // !neko_lang_ast_hpp

