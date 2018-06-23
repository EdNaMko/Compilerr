#pragma once
#include <string>

enum {
	FUNCTION,
	INDETIFIER,
	OPERATOR,
	NUMBER
};
 
class Token
{
public:
	virtual std::string getName() const =0;
	virtual int getType() const = 0;
	virtual void print() const = 0;
	virtual void setName(std::string) = 0;
	virtual void setType(int) = 0;
};