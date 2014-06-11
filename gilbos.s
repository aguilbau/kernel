%define STACK_BASE	0x8000
%define BOOT_SEG	0x07c0
%define KSIZE		0x0002

[org 0x0]

mov		ax, BOOT_SEG
mov		ds, ax
mov		es, ax

mov		bp, STACK_BASE	; set stack
mov		ss, bp
mov		sp, 0xf000

mov		bx, OS_MSG
call	putstr

mov		bx, KSIZE
call	disk_load

mov		bx, KERNEL_MSG
call	putstr

;mov		bx, 0x9000
;mov		dh, 5
;call	disk_load

jmp		$

%include 'bios_routines.s'


; DATA
OS_MSG:
db		'booting os', 0

KERNEL_MSG:
db		'kernel loaded', 0

DISK_ERROR:
db		'disk read error', 0


; Padding
times 510 -( $ - $$ ) db 0
; BIOS magic
dw 0xaa55
