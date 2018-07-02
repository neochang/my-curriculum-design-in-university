data_seg segment
a dw 10,20,30,33,45,200,37,3,5,7,11,23,49,56,17
b dw 10,20,30,11,33,37,1,2,3,4,5,6,7,8,9,100,99,88,77,66
c dw 15 dup('@')
data_seg ends

code  segment 
      assume cs:code,ds:data_seg
start:mov ax,data_seg
      mov ds,ax
      mov bx,0
      mov si,0
      mov cx,15
loop1:push cx
      mov di,0
      mov cx,20
      mov ax,a[si]
loop2:cmp b[di],ax
      jne no
      mov c[bx],ax
      add bx,2
      jmp yes
no:   add di,2
      loop loop2
yes:  add si,2
      pop cx
      loop loop1
      mov ah,4ch
      int 21h
code  ends
      end start

