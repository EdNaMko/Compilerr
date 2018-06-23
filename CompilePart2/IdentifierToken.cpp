#include "stdafx.h"
#include "IdentifierToken.h"


IdentifierToken::IdentifierToken(std::string name)
	:name(name),
	type(INDETIFIER)
{
}


IdentifierToken::~IdentifierToken()
{
}

std::string IdentifierToken::getName() const
{
	return name;
}

void IdentifierToken::print() const
{

}

void IdentifierToken::setName(std::string info)
{
	name = info;
}

void IdentifierToken::setType(int tp) {
	type = tp;
}

int IdentifierToken::getType() const
{
	return type;
}