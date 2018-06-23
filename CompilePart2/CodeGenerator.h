#pragma once
#include "Parser.h"
#include <vector>
#include <map>
#include<fstream>
class CodeGenerator
{
public:
	CodeGenerator();
	~CodeGenerator();
	void codeGenerator(Node*,std::map<std::string,double>& identPool,bool&);
	bool isNotOperator(Node*) const;
	bool isNotNumber(Node*) const;
	void execute(std::ifstream&);
	bool isCorrectName(std::string)const;
	bool isLetter(char) const;
	bool isNotKeywordName(std::string)const;
private:
	std::ofstream fcode;
	std::ofstream fdata;
	std::ofstream func;
	std::ofstream output;
};

