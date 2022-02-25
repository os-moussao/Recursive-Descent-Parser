#include "rdp_calc.h"

// Grammar:
// <expression>	::= <term> {("+" | "-") <term>}
// <term>		::= <factor> {("*" | "/") <factor>}
// <factor>		::= <number> | "(" <expression> ")"
// <number>		::= positive integer


// global variable holding the current Symbol
Node *Symp;

// Some expressions have many syntax errors, do not print them all
// print only the first error encountered, and set error_free to 0
bool	error_free;

// Parser function
ASTreeNode_t *parser(lexer_t *tokens)
{
	initSymp;

	error_free = 1;
	ASTreeNode_t *ASTree = expression();
	if (ASTree == NULL || (Symp && !isEnd)) {
		ast_clear(ASTree);
		if (Symp)
			unexpect("parser");
		return (NULL);
	}

	return ASTree;
}

int accept(token_t token)
{
	if (Sym == token) {
		nextSymp;
		return 1;
	}
	return 0;
}

int expect(token_t expected_token)
{
	if (!accept(expected_token)) {
		
		// check if this is the first error in the expression
		if (!error_free)
			return 0;
		
		// if so, process the error
		if (Sym == endofexpr || Sym == number)
			error("expect: found %s when expecting a '%s'\n", lexeme[Sym], lexeme[expected_token]);

		else
			error("expect: found '%s' when expecting a '%s'\n", lexeme[Sym], lexeme[expected_token]);
		
		// lock: set error_free to 0
		error_free = 0;

		return 0;
	}
	return 1;
}

void unexpect(char *msg)
{
	// check if this is the first error in the expression
	if (!error_free)
		return ;

	// if so, process the error
	if (msg && *msg)
		error("%s: ", msg);
	error("unexpected token '%s' ", lexeme[Sym]);
	if (Symp->prev)
		error("after '%s'\n", lexeme[Symp->prev->tok]);
	else
		error("in the beginning of the expression\n");
	
	// lock: set error_free to 0
	error_free = 0;
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
	{
		unexpect("factor");
		return NULL;
	}
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

	while (!isEnd && (Sym == mult || Sym == div_)) {
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

	while (!isEnd && (Sym == plus || Sym == minus)) {
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