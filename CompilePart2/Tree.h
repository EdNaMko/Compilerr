#pragma once
#include "Token.h"
#include <stack>
#include <deque>

struct Node {
	Node* left;
	Node* right;
	Token* val;
	//int type;
};

class Tree
{
public:
	Tree();
	~Tree();
	Node* create(std::deque<Token*>);
	bool isOperator(std::string) const;
	bool isDigit(std::string) const;
	bool isIdentifier(std::string) const;
	Node* makeNode(Token*);
	int priority(std::string);
	void attachOperator(std::stack<Node*>&, std::stack<Node*>&);
	
};

