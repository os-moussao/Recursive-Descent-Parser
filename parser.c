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
	if (ASTree == NULL || Symp) {
		ast_clear(ASTree);
		error("parser: syntax error\n");
		return (NULL);
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
	if (!Symp || !accept(token)) {
		error("expect: unexpected token\n");
		return 0;
	}
	return 1;
}

// <factor>		::= <number> | "(" <expression> ")"
ASTreeNode_t *factor()
{
	ASTreeNode_t *tree = NULL;

	if (!Symp)
		return NULL;

	if (Sym == number) {
		tree = ast_new(Sym, Val, NULL, NULL);
		nextSymp;
		return tree;
	}

	else if (accept(opar)) {

		tree = expression();

		if (tree == NULL || !expect(cpar)) {
			ast_clear(tree);
			return NULL;
		}

		return tree;
	}

	else
		return NULL;
}


// <term> ::= <factor> {("*" | "/") <factor>}
ASTreeNode_t *term()
{
	ASTreeNode_t *tree = NULL;

	if (!Symp)
		return NULL;

	tree = factor();
	if (tree == NULL) {
		return NULL;
	}

	while (Symp && (Sym == mult || Sym == div_)) {
		tree = ast_new(Sym, none, tree, NULL);
		nextSymp;

		tree->right = factor();
		if (tree->right == NULL) {
			ast_clear(tree);
			return NULL;
		}
	}

	return tree;
}

// <expression>	::= <term> {("+" | "-") <term>}
ASTreeNode_t *expression()
{
	ASTreeNode_t *tree = NULL;

	if (!Symp)
		return NULL;

	tree = term();
	if (tree == NULL) {
		return NULL;
	}

	while (Symp && (Sym == plus || Sym == minus)) {
		tree = ast_new(Sym, none, tree, NULL);
		nextSymp;

		tree->right = term();
		if (tree->right == NULL) {
			ast_clear(tree);
			return NULL;
		}
	}

	return tree;
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