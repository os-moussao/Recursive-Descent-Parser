#include "rdp_calc.h"

const char *names[] = {
	"number", "opar", "cpar", "plus", "minus", "mult", "div_", "unknown"
};

void dispTokens(Node *tokens)
{
	while (tokens) {
		printf("%s\n", names[tokens->tok]);
		tokens = tokens->next;
	}
}