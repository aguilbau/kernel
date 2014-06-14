#include "screen.h"
#include "gdt.h"

int		main(void);

void		_start(void)
{
	clear_screen();
	populate_gdt();
	asm("	movw $0x18, %ax	\n \
			movw %ax, %ss \n \
			movl $0x20000, %esp \n");
	main();
}

int		main(void)
{
	putstr("GDT loaded.\n");
	while (1)
		;
}
