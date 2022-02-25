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
	ASTreeNode_t *AbstractSyntaxTree;

	while (true)
	{
		prompt(expr);

		if (!*expr)
			continue ;

		tokens = lexer(expr);

		if (!tokens)
			continue ;

		if (tokens->len <= 1) {
			list_clear(tokens);
			continue ;
		}

		AbstractSyntaxTree = parser(tokens);

		if (!AbstractSyntaxTree)
			continue ;

		// displays
		displayASTree(AbstractSyntaxTree);
		displayExpression(AbstractSyntaxTree);
		printf("%s\nResult: %d\n", KGRN, eval(AbstractSyntaxTree));
		printf(KNRM);

		// Clear memory
		list_clear(tokens);
		ast_clear(AbstractSyntaxTree);
	}
}