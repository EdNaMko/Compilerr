#include "stdafx.h"
#include "Tree.h"

Tree::Tree()
{
}


Tree::~Tree()
{
}

bool Tree::isOperator(std::string op) const
{
	if (op == "+" || op == "-" || op == "*" || op == "/" || op == "=")
		return true;
	return false;
}

bool Tree::isDigit(std::string inp) const
{
	if (inp[0] >= '0' && inp[0] <= '9')
		return true;
	return false;
}

bool Tree::isIdentifier(std::string inp) const
{
	if ((inp[0] >= 'a' && inp[0] <= 'z') || (inp[0] >= 'A' && inp[0] <= 'Z'))
		return true;
	return false;
}

int Tree::priority(std::string op)
{
	if (op == "+" || op == "-")
		return 1;
	else if (op == "*" || op == "/")
		return 2;
	else if (op == "=")
		return 0;
	return -1;
}


Node* Tree::makeNode(Token* info)
{
	Node* newNode = new Node();
	newNode->val=info;
	newNode->left = NULL;
	newNode->right = NULL;
	return newNode;
}

void Tree::attachOperator(std::stack<Node*>& treeOperands, std::stack<Node*>& treeOperators)
{
	Node* opNode = treeOperators.top();
	treeOperators.pop();

	opNode->left = treeOperands.top();
	treeOperands.pop();

	opNode->right = treeOperands.top();
	treeOperands.pop();

	treeOperands.push(opNode);
}


Node* Tree::create(std::deque<Token*> inp)
{
	std::stack<Token*> input;
	std::string operand;

	for (int i = 0; i < inp.size(); i++)
	{
		if (isDigit(inp[i]->getName()) || isIdentifier(inp[i]->getName()))
			input.push(inp[i]);
		else
			input.push(inp[i]);
	}

	std::stack<Node*> operators;
	std::stack<Node*> treeNodes;
	Token* temp;

	while (!input.empty())
	{
		temp = input.top();
		input.pop();

		if (temp->getType()==NUMBER || temp->getType()==INDETIFIER || temp->getType()==FUNCTION)
		{
			treeNodes.push(makeNode(temp));
		}

		if (temp->getName()==")")
		{
			operators.push(makeNode(temp));
		}

		if (temp->getType()==OPERATOR)
		{
			bool pushed = false;
			while (!pushed)
			{
				if (operators.empty())
				{
					operators.push(makeNode(temp));
					pushed = true;
				}
				else if (operators.top()->val->getName() == ")")
				{
					operators.push(makeNode(temp));
					pushed = true;
				}
				else if (priority(temp->getName()) >= priority(operators.top()->val->getName()))
				{
					operators.push(makeNode(temp));
					pushed = true;
				}
				else
				{
					attachOperator(treeNodes, operators);
				}
			}
		}
		if (temp->getName() == "(")
		{
			while (operators.top()->val->getName() != ")")
			{
				attachOperator(treeNodes, operators);
			}
			operators.pop();
		}
	}

	while (!operators.empty())
	{
		attachOperator(treeNodes, operators);
	}
	return treeNodes.top();
}