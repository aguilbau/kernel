#include "gdt.h"
#include "types.h"

void		load_gdt_desc(uint32_t base, uint32_t limit,
				uint8_t access, uint8_t flags, t_gdt_descriptor *gdt)
{
	gdt->limit_0_15 = (limit & 0xffff);
	gdt->base_0_15 = (base & 0xffff);
	gdt->limit_16_19 = (limit & 0xf0000) >> 16;
	gdt->base_16_23 = (base & 0xff000) >> 16;
	gdt->base_24_31 = (base & 0xff000000) >> 24;
	gdt->access = access;
	gdt->flags = (flags & 0xf);
}

void		populate_gdt()
{
	load_gdt_desc(0x0, 0x0, 0x0, 0x0, &kernel_gdt[0]);
	load_gdt_desc(0x0, 0xfffff, 0x9b, 0x0d, &kernel_gdt[1]);
	load_gdt_desc(0x0, 0xfffff, 0x93, 0x0d, &kernel_gdt[2]);
	load_gdt_desc(0x0, 0x0, 0x97, 0x0d, &kernel_gdt[3]);

	kernel_gdtr.limit = GDT_SIZE * 8;
	kernel_gdtr.base = GDT_BASE;

	asm("lgdtl (kgdtr)");
	asm("movw $0x10, %ax	\n \
		movw %ax, %ds		\n \
		movw %ax, %es		\n \
		movw %ax, %fs		\n \
		movw %ax, %gs		\n \
		ljmp $0x08, $next	\n \
		next:				\n");
}
