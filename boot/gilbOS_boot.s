%define STACK_BASE	0x9000
KERNEL_OFFSET equ 0x1000

[org 0x7c00]

	xor		ax, ax
	mov		ds, ax
	mov		es, ax

;	mov		[BOOT_DRIVE], dl
	mov		bp, STACK_BASE
	mov		ss, bp
	mov		sp, STACK_BASE

	mov		bx, OS_MSG
	call	putstr
	mov		bx, REAL_MODE_MSG
	call	putstr

	call	load_kernel
	call	switch_to_protected_mode

%include 'boot/bios_routines.s'
%include 'boot/gdt.s'
%include 'boot/switch_to_protected_mode.s'	

[BITS 16]

load_kernel:
	mov		bx, KERNEL_OFFSET
	mov		dh, 0xf
;	mov		dl, [BOOT_DRIVE]
	call	disk_load
	mov		bx, LOAD_KERNEL_MSG
	call	putstr

	ret

[BITS 32]

begin_protected_mode:
;	call	KERNEL_OFFSET
	jmp		$

;; DATA

;BOOT_DRIVE:
;	db 0

OS_MSG:
	db 'Loading gilbOS', 0
REAL_MODE_MSG:
	db 'Starting in 16-bit protected mode', 0
LOAD_KERNEL_MSG:
	db 'Kernel loaded', 0

times 510-($-$$) db 0			; Padding
dw 0xaa55						; boot magic number
