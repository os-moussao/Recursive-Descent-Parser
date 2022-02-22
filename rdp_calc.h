#pragma once

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

#define MAXSIZE 1024

typedef enum {
	ident, number, opar, cpar, plus, minus, mult, div, mod
} token_t;