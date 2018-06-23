#include "stdafx.h"
#include "OperatorToken.h"


OperatorToken::OperatorToken(std::string name)
	:name(name),
	type(OPERATOR)
{
	priority = getPrecedence(name);

	if (name == "*")
		opType = MULTIPLY;
	else if (name == "/")
		opType = DIVIDE;
	else if (name == "+")
		opType = SUMMARY;
	else if (name == "-")
		opType = DIFFERENCE;
	else if (name == ")")
		opType = CloseBracket;
	else if (name == "(")
		opType = OpenBracket;
}


OperatorToken::~OperatorToken()
{
}

std::string OperatorToken::getName() const
{
	return name;
}

int OperatorToken::getPrecedence(std::string op) const
{
	if (op == "+" || op == "-")
		return 1;
	else if (op == "*" || op == "/")
		return 2;
	else if (op == "=")
		return 0;
	return -1;
}

void OperatorToken::print() const
{

}

int OperatorToken::getType() const
{
	return type;
}

void OperatorToken::setName(std::string info)
{
	name = info;
}

void OperatorToken::setType(int tp) {
	type = tp;
}