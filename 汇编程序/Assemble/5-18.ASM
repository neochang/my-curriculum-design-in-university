data segment
   grade dw 59,60,35,68,24,98,67,94,32,28,69,88,69,49,27,19,99,67,64,78,49,30,90,80,58,27,69,91,65,39
   rank dw 30 dup(?)
data ends

code	segment
   assume cs:code,ds:data
start:
   mov ax,data
   mov ds,ax

   mov bp,0
   mov bx,0
   mov di,31
   mov si,0
   mov dx,1
   
   
loop0: dec di
       jz exit
       mov dx,1
       mov rank[si],dx
       mov bp,0
       
       
       mov cx,30

compare: mov ax,grade[bx]
         cmp ax,grade[bp]
         jl count
         jmp continue
       
    
count:    add dx,1
          mov rank[si],dx

continue: add bp,2
          loop compare
          

          add bx,2          ;next student
          add si,2
          jmp loop0
  
exit:   mov ah,4ch
	int 21h
code	ends
	end  start