#include "screen.h"

void		_start(void)
{
	clear_screen();
	putstr("Loading new GDT..\n");
	populate_gdt();

	asm("	movw $0x18, %ax	\n \
			movw %ax, %ss \n \
			movl $0x20000, %esp \n");
	main();
}

void		main(void)
{
	putstr("GDT loaded.\n");
	while (1)
		;
}
