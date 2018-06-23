#include "stdafx.h"
#include "NumberToken.h"


NumberToken::NumberToken(std::string name)
	:name(name),
	type(NUMBER)
{
}


NumberToken::~NumberToken()
{
}

std::string NumberToken::getName() const
{
	return name;
}

void NumberToken::print() const
{

}

void NumberToken::setName(std::string info)
{
	name = info;
}

void NumberToken::setType(int tp) {
	type = tp;
}

int NumberToken::getType() const
{
	return type;
}