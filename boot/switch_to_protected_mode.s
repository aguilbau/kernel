switch_to_protected_mode:
	cli
	lgdt	[gdt_descriptor]
	mov		eax, cr0
	or		eax, 0x1
	mov		cr0, eax

	jmp		CODE_SEG:init_protected_mode

[BITS 32]
	
init_protected_mode:
	mov		ax, DATA_SEG
	mov		ds, ax
	mov		ss, ax
	mov		es, ax
	mov		fs, ax
	mov		gs, ax
	mov		ebp, STACK_BASE
	mov		esp, ebp
	call	begin_protected_mode
