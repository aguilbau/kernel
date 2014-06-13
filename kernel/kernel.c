#include "screen.h"

void		_start(void)
{
	clear_screen();
	putstr("cacadillac");
	putstr("\nlolellol");
	scroll_up();
	while (1)
		;
}
