#pragma once
#include "Token.h"

enum {
	SUMMARY,
	DIFFERENCE,
	MULTIPLY,
	DIVIDE,
	CloseBracket,
	OpenBracket
};

class OperatorToken :
	public Token
{
public:
	OperatorToken(std::string);
	~OperatorToken();
	virtual std::string getName() const;
	virtual void print() const;
	virtual int getType() const;
	virtual void setName(std::string);
	virtual void setType(int);
private:
	std::string name;
	int priority;
	int type;
	int opType;

	int getPrecedence(std::string)const;
};

