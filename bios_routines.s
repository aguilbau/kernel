putstr:
push	ax
loop:
mov		ah, 0x0e
mov		al, [bx]
cmp		al, 0
je		end
int		0x10
add		bx, 1
jmp		loop
end:
mov		al, 0x0a
int		0x10
mov		al, 0x0d
int		0x10
pop		ax
ret

disk_load:
push	dx
mov		ah, 0x02	; BIOS read sector function
mov		al, dh
xor		ch, ch
xor		dh, dh
mov		cl, 0x02
int		0x13
jc		disk_error
pop		dx
cmp		dh, al
jne		disk_error
ret

disk_error:
mov		bx, DISK_ERROR
call	putstr
jmp		$

