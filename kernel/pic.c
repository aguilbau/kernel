#include "pic.h"
#include "io.h"

void				init_pic(void)
{
	unsigned char	imr;

	out(PIC1, 0x11);
	out(PIC2, 0x11);
	
	out(PIC1_DATA, 0x20);
	out(PIC2_DATA, 0x70);

	out(PIC1_DATA, 0x04);
	out(PIC2_DATA, 0x02);

	out(PIC1_DATA, 0x01);
	out(PIC2_DATA, 0x01);

	imr = in(0x21);
	imr = imr & 0xef;
	out(PIC1_DATA, imr);

	out(PIC1, PIC_EOI);
}
