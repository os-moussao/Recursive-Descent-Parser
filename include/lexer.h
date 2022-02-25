#pragma once

#include "rdp_calc.h"

typedef enum {
	number, opar, cpar, plus, minus, mult, div_, unknown
} token_t;

typedef struct Node {
	token_t tok;
	int     val; // if tok == number
	struct Node *next;
	struct Node *prev;
} Node;

typedef struct lexer_s {
	Node *top;
	Node *bottom;
	int len;
} lexer_t;

/**
 * Lexer function
 */
lexer_t	*lexer(char *expr);

/**
 * list utils
 */
lexer_t	*new_list(void);
Node *new_node(token_t tok, int val);
Node *push_front(lexer_t *tokens, Node *new);
Node *push_back(lexer_t *tokens, Node *new);
Node *del_front(lexer_t *tokens);
Node *del_back(lexer_t *list);
void list_clear(lexer_t *list);