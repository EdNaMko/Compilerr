#include "stdafx.h"
#include "Parser.h"


Parser::Parser()
{
}


Parser::~Parser()
{
}

Node* Parser::parse(std::string inpString)
{
	Tokenizer lexer;
	Tree tree;

	std::deque<Token*> input = lexer.lexer(inpString);
	return tree.create(input);
}