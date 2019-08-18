#include "MathUtil.h"

int AlignToMultiple(int a, int divisor)
{
	if (divisor <= 1)
		return a;

	if ((a % divisor) == 0)
		return a;

	return a + divisor - (a % divisor);
}