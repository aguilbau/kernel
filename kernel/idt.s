	;; build interrupt descriptor table
	;; currently only handles keyboard i/o

%define INTGATE			0x8e00
%define IDT_BASE		0x800
%define IDT_ENTRY_NB	0xff

	mov		eax, IDT_BASE
	mov		ebx, default_int
	mov		ecx, IDT_ENTRY_NB
	call	populate_idt

	lidt	[idt_pointer]
;	sti

populate_idt:
	mov		edx, ebx
	shr		edx, 0x10
	mov		[idt_descriptor], bx
	mov		[idt_descriptor + 6], dx
	mov		edi, eax
fill_idt_pic:
	mov		esi, idt_descriptor
	movsd
	movsd
	loop	fill_idt_pic
	ret

default_int:
	iret

idt_pointer:
	dw IDT_ENTRY_NB << 3
	dd IDT_BASE

idt_descriptor:
	dw 0, 8, INTGATE, 0
