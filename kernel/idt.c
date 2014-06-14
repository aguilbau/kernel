#include "idt.h"
#include "stdfuns.h"
#include "interrupt.h"

t_idt_descriptor	kernel_idt[IDT_SIZE];
t_idtr				kernel_idtr;

void				int_default_wrapper(void);
void				int_irq_0_wrapper(void);
void				int_irq_1_wrapper(void);

void			load_idt_descriptor(uint32_t offset, uint16_t selector,
					uint8_t type_attr, t_idt_descriptor *desc)
{
	desc->offset_1 = (offset & 0xffff);
	desc->offset_2 = (offset & 0x0000ffff) >> 16;
	desc->selector = selector;
	desc->zero = 0;
	desc->type_attr = type_attr;
}

void			populate_idt(void)
{
	int			i;

	i = 0;
	while (i < IDT_SIZE)
		load_idt_descriptor((uint32_t)int_default_wrapper, 0x08, INT_GATE, &kernel_idt[i++]);
	load_idt_descriptor((uint32_t)int_irq_0_wrapper, 0x08, INT_GATE, &kernel_idt[32]);
	load_idt_descriptor((uint32_t)int_irq_1_wrapper, 0x08, INT_GATE, &kernel_idt[33]);

	kernel_idtr.limit = IDT_SIZE * 8;
	kernel_idtr.base = IDT_BASE;

	memcpy((void *)kernel_idtr.base, (void *)kernel_idt, kernel_idtr.limit);

	__asm__("lidtl (kernel_idtr)");
}
