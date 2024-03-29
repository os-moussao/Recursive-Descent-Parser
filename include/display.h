#pragma once

#include "rdp_calc.h"

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

extern const char	*name[TOKENS_NUMBER];
extern const char	*lexeme[TOKENS_NUMBER];

void displayTokens(Node *tokens);
void displayExpression(ASTreeNode_t *tree);
void displayASTree(ASTreeNode_t *tree);
void error(char *format, ...);