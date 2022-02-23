#include "rdp_calc.h"

// Grammar:
// <expression>	::= <term> {("+" | "-") <term>}
// <term>		::= <factor> {("*" | "/") <factor>}
// <factor>		::= <number> | "(" <expression> ")"
// <number>		::= positive integer


// global variable holding the current Symbol
Node *Symp;

// Parser function
ASTreeNode_t *parser(lexer_t *tokens)
{
	initSymp;

	ASTreeNode_t *ASTree = expression();
	if (ASTree == NULL) {
		error("parser: syntax error\n");
	}

	return ASTree;
}

int	accept(token_t token)
{
	if (Sym == token) {
		nextSymp;
		return 1;
	}
	return 0;
}

int expect(token_t token)
{
	if (!accept(token)) {
		error("expect: unexpected token");
		return 0;
	}
	return 1;
}


// Constructor function
ASTreeNode_t *ast_new(token_t type, int value, ASTreeNode_t *left, ASTreeNode_t *right)
{
	ASTreeNode_t *node;

	node = (ASTreeNode_t *)malloc(sizeof(ASTreeNode_t));
	node->type = type;
	node->value = value;
	node->left = left;
	node->right = right;

	return node;
}

// Destructor function
void	ast_clear(ASTreeNode_t *tree)
{
	if (tree == NULL)
		return ;
	ast_clear(tree->left);
	ast_clear(tree->right);
	free(tree);
}