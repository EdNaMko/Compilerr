#include "stdafx.h"
#include "CodeGenerator.h"
#include <iostream>
#include <assert.h>
#include "FunctionToken.h"
CodeGenerator::CodeGenerator()
{
	fcode.open("code.txt");
	fdata.open("data.txt");
	fdata << ".data" << std::endl;
	func.open("func.txt");
}


CodeGenerator::~CodeGenerator()
{
	output.open("Output.txt");
	fdata.close();
	fcode << "EXIT";
	fcode.close();
	func.close();
	std::ifstream in1;
	in1.open("data.txt");
	char c;
	do
	{
		c = in1.get();
		if (c != EOF) {
			output.put(c);
		}
	} while (c != EOF);

	in1.close();
	output.put('\n');
	std::ifstream in2;
	in2.open("code.txt");
	output << ".code\n";
	do
	{
		c = in2.get();
		if (c != EOF) {
			output.put(c);
		}
	} while (c != EOF);
	in2.close();
	output.put('\n');
	std::ifstream in3;
	in3.open("func.txt");
	do
	{
		c = in3.get();
		if (c != EOF) {
			output.put(c);
		}
	} while (c != EOF);
	in3.close();
	output.close();

}

bool CodeGenerator::isNotOperator(Node* root) const
{
	if (root->val->getName() != "+" && root->val->getName() != "-" && root->val->getName() != "*" && root->val->getName() != "/")
		return true;
	return false;
}

bool CodeGenerator::isNotNumber(Node* root) const
{
	if ((root->val->getName()[0] >= '0' && root->val->getName()[0] <= '9'))
		return false;
	if (root->val->getName()[0] == '-')
	{
		if (root->val->getName()[1] >= '0' && root->val->getName()[1] <= '9')
			return false;
	}
	return true;
}

bool CodeGenerator::isLetter(char inp) const
{
	if ((inp >= 'a' && inp <= 'z') || (inp >= 'A' && inp <= 'Z'))
	{
		return true;
	}
	return false;
}

bool CodeGenerator::isCorrectName(std::string inp) const
{
	bool isnum = false;
	if (isLetter(inp[0]) || inp[0] == '_')
	{
		for (int i = 1; i < inp.length(); i++)
		{
			if (inp[i] >= '0' && inp[i] <= '9')
			{
				isnum = true;
			}
			else if (isLetter(inp[i]) && isnum==true)
				return false;
			else if (isLetter(inp[i]) && isnum==false)
				continue;
			else
				return false;

		}
		return true;
	}
	else
		return false;
}

bool CodeGenerator::isNotKeywordName(std::string inp) const
{
	if (inp == "ADD" || inp == "SUB" || inp == "MUL" || inp == "DIV"||inp=="MOV")
		return false;
	else if (inp == "ASSIGN" || inp == "LOAD" || inp == "STORE")
		return false;
	return true;
}

void CodeGenerator::codeGenerator(Node* root, std::map<std::string, double>& identPool, bool& isFunc)
{
	static int reg = 0;
	static int count = 0;
	static int argsize = 0;
	static std::deque<std::string>arglist;
	if (root == NULL)
		return;
	if (root->val->getName() == "=")
	{
		bool isCorrName = isCorrectName(root->left->val->getName());
		bool keyword = isNotKeywordName(root->left->val->getName());
		std::string name="";

		if(isCorrName && keyword)
			name = root->left->val->getName();
		else if(!isCorrName){
			std::cout << root->left->val->getName() << std::endl;
			std::cout << "1)The firs charachter can be only Letter or '_'"<<std::endl;
			std::cout << "2)Inner charachters can be Letter or Number" << std::endl;
			std::cout << "3)After Number cannot be Letter" << std::endl;
			assert(isCorrName && "ERROR::UNCORRECT NAME!!");
		}
		else if (!keyword)
		{
			std::cout << root->left->val->getName() << std::endl;
			std::cout << "The varibale or function name can not be a KEYWORD name" << std::endl;
			std::cout << "Keywords name list::" << std::endl;
			std::cout << "1)ADD" << std::endl;
			std::cout << "2)SUB" << std::endl;
			std::cout << "3)MUL" << std::endl;
			std::cout << "4)DIV" << std::endl;
			std::cout << "5)MOV" << std::endl;
			std::cout << "6)ASSIGN" << std::endl;
			std::cout << "7)LOAD" << std::endl;
			std::cout << "8)STORE" << std::endl;
			assert(keyword && "ERROR::NAME is Keyword Name!!");
		}
		
		if (root->left->val->getType() == FUNCTION)
		{
			func << name << "::" << std::endl;
			func << "PUSH SF" << std::endl;
			identPool.insert(std::pair<std::string, bool>(name, true));
			isFunc = true;
			Token* pda = root->left->val;
			FunctionToken* pd = dynamic_cast<FunctionToken*>(pda);
			argsize = pd->getArgSize();
			arglist = pd->getArgList();
			codeGenerator(root->right,identPool, isFunc);
			reg -= 4;
			func << "POP SF" << std::endl;
			func << "RET" << std::endl;
		}
		else if (root->left->val->getType() == INDETIFIER)
		{
			fdata << "DWORD " << name << std::endl;
			identPool.insert(std::pair<std::string, bool>(name, false));
			codeGenerator(root->right,identPool, isFunc);
			reg -= 4;
			fcode << "ASSIGN A2 " << name << std::endl;
			fcode << "STORE R" << reg << " A2" << std::endl;
			fcode << std::endl;
		}
	}
	else {
		codeGenerator(root->left,  identPool, isFunc);
		codeGenerator(root->right, identPool, isFunc);

		if (root->val->getType() == NUMBER)
		{
			if (!isFunc)
			{
				fcode << "ASSIGN R" << reg << " " << root->val->getName() << std::endl;
				reg += 4;
			}
			else
			{
				func << "ASSIGN R" << reg << " " << root->val->getName() << std::endl;
				reg += 4;
			}
		}
		else if (root->val->getType() == OPERATOR)
		{
			if (root->val->getName() == "+")
			{
				int add = reg - 4;
				reg -= 8;
				if(!isFunc)
					fcode << "ADD R" << reg << " R" << add << std::endl;
				else
					func << "ADD R" << reg << " R" << add << std::endl;
				reg += 4;
			}
			else if (root->val->getName() == "-")
			{
				int sub = reg - 4;
				reg -= 8;
				if (!isFunc)
					fcode << "SUB R" << reg << " R" << sub << std::endl;
				else
					func << "SUB R" << reg << " R" << sub << std::endl;
				reg += 4;
			}
			else if (root->val->getName() == "*")
			{
				int mul = reg - 4;
				reg -= 8;
				if(!isFunc)
					fcode << "MUL R" << reg <<" R"<<mul<< std::endl;
				else
					func << "MUL R" << reg << " R" << mul << std::endl;
				reg += 4;
			}
			else if (root->val->getName() == "/")
			{
				int div = reg - 4;
				reg -= 8;
				if(!isFunc)
					fcode << "DIV R" << reg << " R" << div << std::endl;
				else
					func << "MUL R" << reg << " R" << div << std::endl;
				reg += 4;
			}
		}
		else if (root->val->getType() == INDETIFIER)
		{
			if (!isFunc)
			{
				std::map<std::string, bool>::iterator it;
				assert(identPool.find(root->val->getName()) != identPool.end() && "Doesn't find this identifier");
					fcode << "ASSIGN A2 " << root->val->getName() << std::endl;
					fcode << "LOAD R" << reg << " " << "A2" << std::endl;
					reg += 4;
			}
			else 
			{
				bool flag = false;
				int tempIndex = 0;
				for (int i = 0; i < arglist.size(); i++)
				{
					if (arglist[i] == root->val->getName())
					{
						flag = true;
						tempIndex = i;
						break;
					}
				}
				if (flag)
				{
					func << "MOV R" << reg << " SF" << std::endl;
					reg += 4;
					func << "ASSIGN R" << reg << " " << 8 + (tempIndex + 1 )* 4 << std::endl;
					reg += 4;
					func << "ADD R" << reg - 8 << " R" << reg - 4 << std::endl;
					reg -= 8;
					func << "MOV A2 R" << reg << std::endl;
					func << "LOAD R" << reg << " A2" << std::endl;
					reg += 4;
				}
				else
				{
					assert(flag && "Doesn't exists that argument");
				}
			}

		}
		else if (root->val->getType() == FUNCTION)
		{
			Token* pda = root->val;
			FunctionToken* pd = dynamic_cast<FunctionToken*>(pda);
			std::map<std::string, bool>::iterator it;

			if (identPool.find(pd->getName()) != identPool.end() && identPool.find(pd->getName())->second == true)
			{
				std::deque<std::string> arglist = pd->getArgList();
				Parser parser;
				for (int i = 0; i < arglist.size(); i++)
				{
					Node* token = new Node();
					token = parser.parse(arglist[i]);

					codeGenerator(token, identPool, isFunc);
					reg -= 4;
				if(!isFunc)
					fcode << "PUSH R" << reg << std::endl;
				else
					func << "PUSH R" << reg << std::endl;
				}
				if(!isFunc)
					fcode << "call " << root->val->getName() << std::endl;
				else
					func << "call " << root->val->getName() << std::endl;
				reg += 4;
				if(!isFunc)
					fcode << "ADD SP " << pd->getArgSize() * 4 << std::endl;
				else
					func << "ADD SP " << pd->getArgSize() * 4 << std::endl;
			}
		}
	}

}

void CodeGenerator::execute(std::ifstream& fin)
	{
		Parser parser;
		Node* node=new Node();
		std::map<std::string, double> identPool;
		while (!fin.eof())
		{
			char inputChar = fin.get();
			std::string expression = "";
			while (inputChar != ';' && !fin.eof())
			{
				expression += inputChar;
				inputChar = fin.get();
			}
			if (!fin.eof())
			{
				node = parser.parse(expression);

				bool isFunc = false;
				int reg = 0;
				codeGenerator(node,identPool,isFunc);
			}
		}
	}