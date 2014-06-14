#ifndef IDT_H
# define IDT_H

# include "types.h"

# define INT_GATE	0x8e
# define IDT_SIZE	0xff
# define IDT_BASE	0x800

typedef struct		s_idt_descriptor
{
	uint16_t		offset_1;
	uint16_t		selector;	// must point to a valid selector in GDT
	uint8_t			zero;
	uint8_t			type_attr;
	uint16_t		offset_2;
} __attribute__ ((packed)) t_idt_descriptor;

/*

 offset (32 bit) is used to specify the routine to execute

 type_attr structure: (http://wiki.osdev.org/Interrupt_Descriptor_Table)

   7                           0
 +---+---+---+---+---+---+---+---+
 | P |  DPL  | S |       G       |
 +---+---+---+---+---+---+---+---+

 P:		Present, can be set to 0 for unused interrupts or for paging
 DPL:	Descriptor Privilege Level, for the calling Descriptor
 S:		Storage Segment. 0 for interrupt gates
 G:		Gate Type.
			0x5: 32 bit taske gate
			0x6: 16 bit interrupt gate
			0x7: 16 bit trap gate
			0xe: 32 bit interrupt gate
			0xf: 32 bit trap gate

*/

typedef struct				s_idtr
{
	uint16_t				limit;
	uint32_t				base;
} __attribute__ ((packed)) t_idtr;

extern t_idt_descriptor		kernel_idt[];
extern t_idtr				kernel_idtr;


#endif /* !IDT_H */
