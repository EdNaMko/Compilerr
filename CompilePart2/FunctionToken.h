#pragma once
#include "Token.h"
#include <deque>

class FunctionToken :
	public Token
{
public:
	FunctionToken(std::string,std::deque<std::string>);
	~FunctionToken();
	virtual std::string getName() const;
	void print() const;
	virtual int getType() const;
	virtual void setName(std::string);
	virtual void setType(int);
	int getArgSize();
	std::deque<std::string> getArgList();
private:
	std::string name;
	std::deque<std::string> arglist;
	int type;
	int size;
};

