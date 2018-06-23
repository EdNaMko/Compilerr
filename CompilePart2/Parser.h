#pragma once
#include "Tree.h"
#include "Tokenizer.h"
class Parser
{
public:
	Parser();
	~Parser();
	Node* parse(std::string);
};

