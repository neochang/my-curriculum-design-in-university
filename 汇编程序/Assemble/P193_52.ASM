

code segment
assume cs:code
start:
      mov ah,1
      int 21h


      cmp al,61h
      jz  next1
      cmp al,7ah
      jz  next2
      sub al,1
      mov dl,al
      mov ah,2
      int 21h
      
      add al,1
      mov dl,al
      mov ah,2
      int 21h
      
      add al,1
      mov dl,al
      mov ah,2
      int 21h
      jmp next
next1: mov al,7ah     
       mov dl,al
       mov ah,2
       int 21h
       
       mov al,61h
       mov dl,al
       mov ah,2
       int 21h

       mov al,62h
       mov dl,al
       mov ah,2
       int 21h
       jmp next

next2: mov al,79h     
       mov dl,al
       mov ah,2
       int 21h
       
       mov al,7ah
       mov dl,al
       mov ah,2
       int 21h

       mov al,61h
       mov dl,al
       mov ah,2
       int 21h

next:  mov ah,4ch
       int 21h
code  ends
       end start

      
      
      
      
      
      
      
      
      
      
 