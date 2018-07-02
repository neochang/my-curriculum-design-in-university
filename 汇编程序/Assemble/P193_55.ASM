code     segment
	assume cs:code
start:
	mov ah,1
	int 21h
	sub al,30h
	mov cl,al
	mov dl,07h
beep:	mov ah,2
	int 21h
	push cx
        mov si,0fffh
bbb:    mov cx,0ffffh
a1:    loop a1
        dec si
        jnz bbb
        pop cx
	loop beep
	mov ah,4ch
	int 21h
code     ends
	end start