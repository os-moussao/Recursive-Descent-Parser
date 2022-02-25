#include "rdp_calc.h"

const char *name[TOKENS_NUMBER] = {
	"number", "opar", "cpar", "plus", "minus", "mult", "div", "end-of-expression", "unknown"
};

const char *lexeme[TOKENS_NUMBER] = {
	"<number>", "(", ")", "+", "-", "*", "/", "end-of-expression", "unknown"
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

void displayExpression_(ASTreeNode_t *tree)
{
	if (tree == NULL)
		return ;

	if (tree->type != number)
		printf("(");

	if (tree->left)
	{
		displayExpression_(tree->left);
		printf(" ");
	}

	if (tree->type == number)
		printf("%d", tree->value);
	else
		printf("%s", lexeme[tree->type]);

	if (tree->right)
	{
		printf(" ");
		displayExpression_(tree->right);
	}

	if (tree->type != number)
		printf(")");
}


void displayExpression(ASTreeNode_t *tree)
{
	printf(KYEL);
	printf("\nExpression Precedence: ");
	printf(KBLU);
	displayExpression_(tree);
	printf(KNRM);
	fflush(stdout);
}

void displayASTree_(ASTreeNode_t *tree, int ident_level)
{
	if (tree == NULL)
		return ;
	for (int i = 0; i < ident_level; i++) {
		printf("├   ");
	}
	printf("├── %s ", name[tree->type]);
	if (tree->type == number)
		printf("(%d)\n", tree->value);
	else
		printf("(%s)\n", lexeme[tree->type]);
	displayASTree_(tree->right, ident_level + 1);
	displayASTree_(tree->left, ident_level + 1);
}

void displayASTree(ASTreeNode_t *tree)
{
	printf("%s\nAbstract Syntax Tree:\n", KYEL);
	printf(KGRN);
	displayASTree_(tree, 0);
	printf(KNRM);
	fflush(stdout);
}

void error(char *format, ...)
{
	va_list ap;

	fprintf(stderr, KRED);
	va_start(ap, format);
	vfprintf(stderr, format, ap);
	va_end(ap);
	fprintf(stderr, KNRM);
	fflush(stderr);
}