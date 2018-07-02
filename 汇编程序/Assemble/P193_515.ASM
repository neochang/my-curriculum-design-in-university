data	segment
    n      dw   10
    M      dw   3,5,-100,9,7,-50,60,78,98,99
   result  dw   0
   addr    dw   ?
data	ends

code	segment
   assume cs:code,ds:data
start:
	mov ax,data
	mov ds,ax

	mov si,0
	mov cx,n
next:	test M[si],8000h
	jnz convert
	mov bx,result
	cmp M[si],bx
	ja exchange
	add si,2
	loop next
	jmp exit

convert: mov ax,M[si]
	mov dx,-1
	imul dx
	mov bx,result
	cmp ax,bx
	ja exchange
	add si,2
	loop next
	jmp exit

exchange: mov dx,M[si]
	mov result,dx
	mov addr,si
	add si,2
	loop next

exit:   mov ah,4ch
	int 21h
code	ends
	end  start