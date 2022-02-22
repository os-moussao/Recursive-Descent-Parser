#pragma once

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

#define MAXSIZE 1024

typedef enum {
	ident, number, opar, cpar, plus, minus, mult, div, mod
} Token;

typedef struct Node {
	Token tok;
	int   val; /* if tok == number */
	struct Node *next;
	struct Node *prev;
} Node;