#include "rdp_calc.h"

int main(void)
{
	char	expr[MAXSIZE];

	while (true)
	{
		printf("Enter expression: ");
		scanf("%[^\n]", expr);
		printf("%s\n", expr);
	}
}