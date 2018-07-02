data	segment
  hex1	db	?
  hex2	db	?
  hex3	db	?
  hex4  db	?
data	ends

code	segment
  assume cs:code,ds:data
start:
	mov ax,data
	mov ds,ax

	mov ah,1
	int 21h
	mov hex1,al

	mov ah,1
	int 21h
	mov hex2,al

	mov ah,1
	int 21h
	mov hex3,al

	mov ah,1
	int 21h
	mov hex4,al
;--------------------
	mov dl,0dh
	mov ah,2
	int 21h
	mov dl,0ah
	mov ah,2
	int 21h
;--------------------
	mov al,hex1
	cmp al,3ah
	jl  num1      ;digit is 0 to 9
	sub al,7h     ;digit is A to F
num1:   sub al,30h
	mov cx,8
display1: shl al,1
	jc one1
	mov dl,31h
	mov ah,2
	int 21h
	jmp next1
one1:    mov dl,30h
	mov ah,2
	int 21h
next1:   loop display1

	mov dl,20h
	mov ah,2
	int 21h

	mov al,hex2
	cmp al,3ah
	jl  num2      ;digit is 0 to 9
	sub al,7h     ;digit is A to F
num2:   sub al,30h
	mov cx,8
display2: shl al,1
	jc one2
	mov dl,31h
	mov ah,2
	int 21h
	jmp next2
one2:    mov dl,30h
	mov ah,2
	int 21h
next2:   loop display2

	mov dl,20h
	mov ah,2
	int 21h

	mov al,hex3
	cmp al,3ah
	jl  num3      ;digit is 0 to 9
	sub al,7h     ;digit is A to F
num3:   sub al,30h
	mov cx,8
display3: shl al,1
	jc one3
	mov dl,31h
	mov ah,2
	int 21h
	jmp next3
one3:    mov dl,30h
	mov ah,2
	int 21h
next3:   loop display3

	mov dl,20h
	mov ah,2
	int 21h

	mov al,hex4
	cmp al,3ah
	jl  num4      ;digit is 0 to 9
	sub al,7h     ;digit is A to F
num4:   sub al,30h
	mov cx,8
display4: shl al,1
	jc one4
	mov dl,31h
	mov ah,2
	int 21h
	jmp next4
one4:    mov dl,30h
	mov ah,2
	int 21h
next4:   loop display4

	mov ah,4ch
	int 21h
code	ends
	end start