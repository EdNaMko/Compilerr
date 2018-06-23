// CmpTry2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Tokenizer.h"
#include <iostream>
#include "Tree.h"
#include <vector>
#include "CodeGenerator.h"
#include <map>
#include <fstream>
void post_order(Node* node)
{
	if (node == NULL)
		return;

	post_order(node->left);
	post_order(node->right);
	std::cout << node->val << " ";
	
}

int main()
{
	std::ifstream fin;
	fin.open("input.txt");
	CodeGenerator code;

	code.execute(fin);
    return 0;
}

