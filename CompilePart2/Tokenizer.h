#pragma once
#include <deque>
#include "Token.h"

class Tokenizer
{
public:
	Tokenizer();
	~Tokenizer();
	std::deque<Token*> lexer(std::string);
private:
	bool isOperator(char) const;
	bool isLetter(char) const;
	Token* makeFunctionToken(std::string,std::deque<std::string>);
	Token* makeIdentifierToken(std::string);
	Token* makeOperatorToken(std::string);
	Token* makeNumberToken(std::string);
};

