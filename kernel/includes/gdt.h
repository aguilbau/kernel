#ifndef GDT_H
# define GDT_H

# include "types.h"

# define GDT_BASE	0x0
# define GDT_SIZE	0xff

typedef struct		s_gdt_descriptor
{
	uint16_t		limit_0_15;
	uint16_t		base_0_15;
	uint8_t			base_16_23;
	uint8_t			access;
	uint8_t			limit_16_19:4;
	uint8_t			flags:4;
	uint8_t			base_24_31;
} __attribute__ ((packed)) t_gdt_descriptor;

typedef struct		s_gdtr
{
	uint16_t		limit;
	uint32_t		base;
} __attribute__ ((packed)) t_gdtr;

extern t_gdt_descriptor		kernel_gdt[3];
extern t_gdtr			kernel_gdtr;

void		populate_gdt();

#endif /* ! GDT_H */
