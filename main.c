#include "rdp_calc.h"

void prompt(char *expr)
{
	printf("Enter expression: ");
	fflush(stdout);
	int nbytes = read(0, expr, MAXSIZE);
	expr[nbytes] = '\0';
}

int main(void)
{
	char	expr[MAXSIZE];
	lexer_t *tokens;

	while (true)
	{
		prompt(expr);

		tokens = lexer(expr);

		if (!tokens)
			continue ;

		// * debug
		dispTokens(tokens->top);
		// * debug

		list_clear(tokens);
	}
}