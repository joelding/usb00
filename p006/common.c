#include "common.h"

void delayms(u16 x)
{
	u16 i, j;

	for (i = 0; i < x; ++i)
		for (j = 0; j < 227; ++j);
}

