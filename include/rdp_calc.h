#pragma once

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include "lexer.h"

#define MAXSIZE 1024

void dispTokens(Node *tokens);