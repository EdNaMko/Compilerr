#pragma once
#include "Token.h"
class IdentifierToken :
	public Token
{
public:
	IdentifierToken(std::string);
	~IdentifierToken();
	virtual std::string getName() const;
	virtual void print() const;
	virtual int getType() const;
	virtual void setName(std::string);
	virtual void setType(int);
private:
	std::string name;
	int type;
};

