data	segment
   count_p   db  0
   count_n   db  0
   M         db  -10,2,-9,4,-8,-7,5,-6,6,7,8,-5,-4,9,10,-3,-2
   num  equ $-M
   P         db 20 dup(?)
   N         db 20 dup(?)
data	ends

code	segment
   assume cs:code,ds:data
start:
	mov  ax,data
	mov  ds,ax

	mov  cx,num
	mov  si,0
juge:   cmp  M[si],0
	jg   positive
	mov  bl,M[si]
	push si
	mov  si, word ptr count_n
	mov  N[si],bl
	inc  count_n
	pop  si
	add  si,1
	loop juge
	jmp  exit
positive: mov bl,M[si]
	push si
	mov  si, word ptr count_p
	mov  P[si],bl
	inc  count_p
	pop  si
	add  si,1
	loop juge

exit:   mov  dl,50h
	mov  ah,2
	int  21h  ;print 'P' on the screen

	mov dl,3ah
	mov ah,2
	int 21h   ;print ':' on the screen

	mov dl,count_p
	add dl,30h
	mov ah,2
	int 21h

	mov dl,0dh
	mov ah,2
	int 21h
	mov dl,0ah
	mov ah,2
	int 21h

	mov dl,4eh
	mov ah,2
	int 21h   ;print 'N' on the screen

	mov dl,3ah
	mov ah,2
	int 21h

	mov dl,count_n
	add dl,30h
	mov ah,2
	int 21h

	mov ah,4ch
	int 21h
code	ends
	end start