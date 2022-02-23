#include "rdp_calc.h"

const char *name[] = {
	"number", "opar", "cpar", "plus", "minus", "mult", "div_", "unknown"
};

const char *lexeme[] = {
	"", "(", ")", "+", "-", "*", "/", "unknown"
};

void displayTokens(Node *tokens)
{
	printf("Tokens Begin:\n");
	while (tokens) {
		printf("%s\n", name[tokens->tok]);
		tokens = tokens->next;
	}
	printf("Tokens End:\n");
	fflush(stdout);
}
}