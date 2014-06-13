%define STACK_BASE	0x9000
KERNEL_OFFSET equ 0x1000

[org 0x7c00]

	xor		ax, ax
	mov		ds, ax
	mov		es, ax

	mov		bp, STACK_BASE
	mov		ss, bp
	mov		sp, STACK_BASE

	call	load_kernel
	call	switch_to_protected_mode

%include 'boot/bios_routines.s'
%include 'boot/gdt.s'
%include 'boot/switch_to_protected_mode.s'

[BITS 16]

load_kernel:
	mov		bx, KERNEL_OFFSET
	mov		dh, 0xf
	call	disk_load

	ret

[BITS 32]

begin_protected_mode:
	jmp		KERNEL_OFFSET

times 510-($-$$) db 0			; Padding
dw 0xaa55						; boot magic number
