data	segment
   ENG    DB   'THE SUN IS SHINING. SUN SUN SUN SUNNN SUKKK SUN$'
   count  DB   0
data	ends

code	segment
  assume cs:code,ds:data
start:
	mov ax,data
	mov ds,ax
	mov si,0
compare: cmp ENG[si],24h
	je exit
	cmp ENG[si],53h
	je nextu
	inc si
	jmp compare

nextu:  inc si
	cmp ENG[si],24h
	je exit
	cmp ENG[si],55h
	je nextn
	inc si
	jmp compare

nextn:  inc si
	cmp ENG[si],24h
	je exit
	cmp ENG[si],4eh
	jne donext
	inc count
donext: inc si
	jmp compare

exit:   mov dl,53h
	mov ah,2
	int 21h
	mov dl,55h
	mov ah,2
	int 21h
	mov dl,4eh
	mov ah,2
	int 21h

	mov dl,count
	add dl,30h
	mov ah,2
	int 21h

	mov ah,4ch
	int 21h
code	ends
	end start