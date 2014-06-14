#ifndef PIC_H
# define PIC_H

/*

 = ICW1
	|0|0|0|1|x|0|x|x|
			 |   | +--- with ICW4 (1), without (0)
			 |	 +----- one controler (1), or multiple (0)
			 +--------- ?

 = ICW2
	|x|x|x|x|x|0|0|0|
	 | | | | |
	 +----------------- base address for interruption vectors
   This address is an offset in the Interruption Descriptr Table.

 = ICW3
	|x|x|x|x|x|x|x|x|
	 | | | | | | | |
	 +----------------- 

 = ICW4
	|0|0|0|x|x|x|x|1|
		   | | | +----- automatic end of interrupt (1)
		   | | +------- buffered mode, (0) for slave, (1) for master
		   | +--------- buffered mode (1)
		   +----------- fully nested mode (1)

*/

# define PIC1				0x20 /* IO base address for master PIC */
# define PIC2				0xA0 /* IO base address for slave PIC */
# define PIC1_COMMAND		PIC1
# define PIC1_DATA			(PIC1+1)
# define PIC2_COMMAND		PIC2
# define PIC2_DATA			(PIC2+1)

# define PIC_EOI			0x20

void			init_pic(void);

#endif /* !PIC_H */
