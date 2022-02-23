#include "rdp_calc.h"

int eval(ASTreeNode_t *ASTree)
{
	if (!ASTree)
		return INT_MIN;

	token_t	type = ASTree->type;
	
	if (type == number)
		return ASTree->value;

	int left = eval(ASTree->left);
	int right = eval(ASTree->right);

	switch (type)
	{
		case plus:
			return left + right;
		case minus:
			return left - right;
		case mult:
			return left * right;
		case div_:
		{
			if (right == 0) {
				error("\nError: division by zero");
				return left > 0? INT_MAX: left != 0? INT_MIN: 0;
			}
			return left / right;
		}
		default:
			return INT_MAX;
	}
}