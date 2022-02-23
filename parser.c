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
