#include "rdp_calc.h"

int lexer_atoi(char **expr)
{
	int	res;

	res = 0;
	while (**expr >= '0' && **expr <= '9')
		res = res * 10 + *(*expr)++ - '0';
	return (res);
}

token_t getToken(char c)
{
	switch (c)
	{
		case '(':
			return opar;
		case ')':
			return cpar;
		case '+':
			return plus;
		case '-':
			return minus;
		case '*':
			return mult;
		case '/':
			return div_;
		default:
			return unknown;
	}
}

lexer_t	*lexer(char *expr)
{
	lexer_t *tokens;

	tokens = new_list();
	while (*expr)
	{
		if (isspace(*expr)) {
			expr++;
			continue ;
		}
		else if (isdigit(*expr)) {
			push_back(tokens, new_node(number, lexer_atoi(&expr)));
		}
		else {
			token_t token = getToken(*expr);
			if (token == unknown)
			{
				error("lexer: unknown token '%c'\n", *expr);
				list_clear(tokens);
				return NULL;
			}
			push_back(tokens, new_node(token, 0));
			expr++;
		}
	}
	return tokens;
}

/**
 * @brief lexer utils bellow
 * All I need to create/destroy a list of tokens
 */

lexer_t	*new_list(void)
{
	lexer_t	*tokens;

	tokens = (lexer_t *)malloc(sizeof(lexer_t));
	tokens->len = 0;
	tokens->top = NULL;
	tokens->bottom = NULL;
	return (tokens);
}

Node *new_node(token_t tok, int val)
{
	Node *new;

	new = (Node *)malloc(sizeof(Node));
	new->tok = tok;
	new->val = val;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

Node *push_front(lexer_t *tokens, Node *new)
{
	new->next = tokens->top;
	if (tokens->top)
		tokens->top->prev = new;
	else
		tokens->bottom = new;
	tokens->top = new;
	(tokens->len)++;
	return (new);
}

Node *push_back(lexer_t *tokens, Node *new)
{
	new->prev = tokens->bottom;
	if (tokens->bottom)
		tokens->bottom->next = new;
	else
		tokens->top = new;
	tokens->bottom = new;
	(tokens->len)++;
	return (new);
}


Node *del_front(lexer_t *tokens)
{
	Node *ret;

	if (tokens->len == 0)
		return (NULL);
	ret = tokens->top;
	tokens->top = tokens->top->next;
	if (tokens->top)
		tokens->top->prev = NULL;
	(tokens->len)--;
	return (free(ret), ret);
}

Node *del_back(lexer_t *list)
{
	Node *ret;

	if (list->len == 0)
		return (NULL);
	ret = list->bottom;
	list->bottom = list->bottom->prev;
	if (list->bottom)
		list->bottom->next = NULL;
	(list->len)--;
	return (free(ret), ret);
}

void	list_clear(lexer_t *list)
{
	while (list->len)
		del_front(list);
	free(list);
}