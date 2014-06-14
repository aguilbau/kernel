#include "gdt.h"
#include "types.h"
#include "stdfuns.h"

t_gdt_descriptor		kernel_gdt[3];
t_gdtr					kernel_gdtr;

void		load_gdt_desc(uint32_t base, uint32_t limit,
				uint8_t access, uint8_t flags, t_gdt_descriptor *desc)
{
	desc->limit_0_15 = (limit & 0xffff);
	desc->base_0_15 = (base & 0xffff);
	desc->limit_16_19 = (limit & 0xf0000) >> 16;
	desc->base_16_23 = (base & 0xff000) >> 16;
	desc->base_24_31 = (base & 0xff000000) >> 24;
	desc->access = access;
	desc->flags = (flags & 0xf);
}

void		populate_gdt()
{
	load_gdt_desc(0x0, 0x0, 0x0, 0x0, &kernel_gdt[0]);
	load_gdt_desc(0x0, 0xfffff, 0x9b, 0x0d, &kernel_gdt[1]);
	load_gdt_desc(0x0, 0xfffff, 0x93, 0x0d, &kernel_gdt[2]);
	load_gdt_desc(0x0, 0x0, 0x97, 0x0d, &kernel_gdt[3]);

	kernel_gdtr.limit = GDT_SIZE * 8;
	kernel_gdtr.base = GDT_BASE;

	memcpy((void *)kernel_gdtr.base, (void *)kernel_gdt, kernel_gdtr.limit);

	asm("lgdtl (kernel_gdtr)");
	asm("movw $0x10, %ax	\r\n \
		movw %ax, %ds		\r\n \
		movw %ax, %es		\r\n \
		movw %ax, %fs		\r\n \
		movw %ax, %gs		\r\n \
		ljmp $0x08, $next	\r\n \
		next:				\r\n");
}
