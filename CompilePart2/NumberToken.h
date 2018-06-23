#pragma once
#include "Token.h"
class NumberToken :
	public Token
{
public:
	NumberToken(std::string);
	~NumberToken();
	std::string NumberToken::getName() const;
	virtual void print() const;
	virtual int getType() const;
	virtual void setName(std::string);
	virtual void setType(int);
private:
	std::string name;
	int type;
};

