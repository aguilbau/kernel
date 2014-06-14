extern int_default
extern int_clock
extern int_keyboard

global int_default_wrapper
global int_irq_0_wrapper
global int_irq_1_wrapper

%define MASTER_PIC	0x20
%define PIC_EOI		0x20

int_default_wrapper:
	call	int_default
	mov		al, PIC_EOI
	out		MASTER_PIC, al
	iret

int_irq_0_wrapper:
	call	int_clock
	mov		al, PIC_EOI
	out		MASTER_PIC, al
	iret

int_irq_1_wrapper:
	call	int_keyboard
	mov		al, PIC_EOI
	out		MASTER_PIC, al
	iret
