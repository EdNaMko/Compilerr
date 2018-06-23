#include "stdafx.h"
#include <iostream>
#include "Tokenizer.h"
#include "FunctionToken.h"
#include "IdentifierToken.h"
#include "NumberToken.h"
#include "OperatorToken.h"

Tokenizer::Tokenizer()
{
}


Tokenizer::~Tokenizer()
{
}

bool Tokenizer::isLetter(char op) const
{
	if ((op >= 'A' && op <= 'Z') || (op >= 'a' && op <= 'z'))
		return true;
	return false;
}

bool Tokenizer::isOperator(char op) const
{
	if (op == '+' || op == '-' || op == '*' || op == '/' || op=='=')
		return true;
	return false;
}


Token* Tokenizer::makeFunctionToken(std::string name, std::deque<std::string >arglist)
{
	Token* ptr =new FunctionToken(name, arglist);
	return ptr;
}

Token* Tokenizer::makeIdentifierToken(std::string name)
{
	Token* ptr = new IdentifierToken(name);
	return ptr;
}

Token* Tokenizer::makeNumberToken(std::string name)
{
	Token* ptr = new NumberToken(name);
	return ptr;
}

Token* Tokenizer::makeOperatorToken(std::string name)
{
	Token* ptr = new OperatorToken(name);
	return ptr;
}

std::deque<Token*> Tokenizer::lexer(std::string input)
{
	std::deque<Token*> tokens;
	std::string name="";
	for (int i = 0; i < input.length(); i++)
	{
		if (isLetter(input[i]))
		{
			name = "";
			while (isLetter(input[i]) || (isdigit(input[i])))
			{
				name += input[i];
				i++;
			}

			if (input[i] == '(')
			{
				std::deque<std::string> arglist;
				std::string arg = "";
				int openbracketcount = 1;
				while ((input[i] != ')' || openbracketcount!=0)  )
				{
					i++;
					if (input[i] == '(')
						openbracketcount++;
					if (input[i] == ')')
						openbracketcount--;
					if (input[i] != ',' && input[i] != ')')
					{
						arg += input[i];
					}
					else if (input[i] == ')' && openbracketcount != 0)
						arg += input[i];
					else {
						arglist.push_back(arg);
						arg = "";
					//	openbracketcount = 1;
					}
				}
				//arglist.push_back(arg);
				i--;
				Token* tok=makeFunctionToken(name, arglist);
				tokens.push_back(tok);
			}
			else {
				i--;
				Token *tok = makeIdentifierToken(name);
				tokens.push_back(tok);
			}
		}
		else if (isdigit(input[i]))
		{
			name = "";
			while (isdigit(input[i]))
			{
				name += input[i];
				i++;
			}
			i--;
			Token* tok = makeNumberToken(name);
			tokens.push_back(tok);
		}
		else if (isOperator(input[i]))
		{
			name = "";
			name += input[i];
			Token* tok = makeOperatorToken(name);
			tokens.push_back(tok);
		}
	}
	return tokens;
}