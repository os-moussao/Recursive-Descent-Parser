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

