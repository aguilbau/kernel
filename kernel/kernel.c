#include "screen.h"
#include "gdt.h"
#include "pic.h"
#include "idt.h"

int			kernel_main(void);

void		_start(void)
{
	clear_screen();

	populate_idt();
	putstr("new IDT loaded\n");
	init_pic();
	putstr("pic initiated\n");

	populate_gdt();
	__asm__("	movw $0x18, %ax	\n \
			movw %ax, %ss \n \
			movl $0x20000, %esp \n");
	kernel_main();
}

int		kernel_main(void)
{
	putstr("GDT loaded.\n");
	while (1)
		;
}
