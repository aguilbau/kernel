#include "screen.h"

void			int_default(void)
{

}

void			int_clock(void)
{
	static int	tic;
	static int	sec;

	tic++;
	if (tic % 100 == 0)
	{
		sec++;
		tic = 0;
		putstr("clock\n");
	}
}

void			int_keyboard(void)
{
	putstr("key\n");
}
