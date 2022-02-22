#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define MAXSIZE 1024



int main(void)
{
	char	expr[MAXSIZE];

	printf("Enter expression: ");
	scanf("%[^\n]", expr);
	printf("%s\n", expr);
}