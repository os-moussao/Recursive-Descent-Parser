#pragma once

#include "rdp_calc.h"

#define initSymp Symp = tokens->top
#define nextSymp Symp = Symp->next
#define Sym      Symp->tok
#define Val      Symp->val
#define isEnd    (Sym == endofexpr)
#define none 0

typedef struct ASTreeNode {
	token_t type;
	int     value;
	struct ASTreeNode *left;
	struct ASTreeNode *right;
}				ASTreeNode_t;

ASTreeNode_t *parser(lexer_t *tokens);

ASTreeNode_t *expression();
ASTreeNode_t *term();
ASTreeNode_t *factor();

int  accept(token_t token);
int  expect(token_t expected_token);
void unexpect(char *msg);

// constructor
ASTreeNode_t *ast_new(token_t type, int value, ASTreeNode_t *left, ASTreeNode_t *right);

// destructor
void	ast_clear(ASTreeNode_t *root);