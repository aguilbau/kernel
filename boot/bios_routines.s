	;; putstr prints a null terminated string
putstr:
	mov		ah, 0x0e
	mov		al, [bx]
	cmp		al, 0
	je		end
	int		0x10
	add		bx, 1
	jmp		putstr

end:
	mov		al, 0x0a
	int		0x10
	mov		al, 0x0d
	int		0x10
	ret

	;; disk_load loads memory from the disk to the ram
disk_load:
	mov		ah, 0x02	; BIOS read sector function
	mov		al, dh
	xor		ch, ch
	xor		dh, dh
	mov		cl, 0x02
	int		0x13
	jc		disk_error
	ret

disk_error:
	mov		bx, DISK_ERROR
	call	putstr
	jmp		$

DISK_ERROR		db 'Disk read error', 0
