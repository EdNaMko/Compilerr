#include "stdafx.h"
#include "FunctionToken.h"
#include <iostream>

FunctionToken::FunctionToken(std::string name, std::deque<std::string> arglist)
	:name(name),
	arglist(arglist),
	type(FUNCTION),
	size(arglist.size())
{
}


FunctionToken::~FunctionToken()
{
}

std::string FunctionToken::getName() const
{
	return name;
}

void FunctionToken::setName(std::string info)
{
	name = info;
}

void FunctionToken::setType(int tp) {
	type = tp;
}

int FunctionToken::getArgSize()
{
	return arglist.size();
}
void FunctionToken::print() const
{
	for (int i = 0; i < arglist.size(); i++)
		std::cout << arglist[i] << "";
}

int FunctionToken::getType() const
{
	return type;
}

std::deque<std::string> FunctionToken::getArgList()
{
	return arglist;
}