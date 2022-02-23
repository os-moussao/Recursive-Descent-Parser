#pragma once

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdarg.h>
#include <limits.h>

#include "lexer.h"
#include "parser.h"
#include "display.h"

#define MAXSIZE 1024

lexer_t       *lexer(char *expr);
ASTreeNode_t  *parser(lexer_t *tokens);
int           eval(ASTreeNode_t *ASTree);