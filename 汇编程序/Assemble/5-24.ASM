branch_addresses    segment
  branch_table    dd     routine_1
                  dd     routine_2
                  dd     routine_3
                  dd     routine_4
                  dd     routine_5
branch_addresses    ends

code        segment
   assume cs:code,ds:branch_addresses

start:
   
   mov bx,branch_addresses
   mov ds,bx

loop1:mov ah,1
      int 21h
      cmp al,31h
      je  routine_1
      cmp al,32h
      je  routine_2
      cmp al,33h
      je  routine_3
      cmp al,34h
      je  routine_4
      cmp al,35h
      je  routine_5
      jmp exit

routine_1: mov dl,52h
           mov ah,2
           int 21h
           mov dl,31h
           mov ah,2
           int 21h
           mov dl,0ah
           mov ah,2
           int 21h
           mov dl,0dh
           mov ah,2
           int 21h
           jmp loop1

routine_2: mov dl,52h
           mov ah,2
           int 21h
           mov dl,32h
           mov ah,2
           int 21h
           mov dl,0ah
           mov ah,2
           int 21h
           mov dl,0dh
           mov ah,2
           int 21h
           jmp loop1

routine_3: mov dl,52h
           mov ah,2
           int 21h
           mov dl,33h
           mov ah,2
           int 21h
           mov dl,0ah
           mov ah,2
           int 21h
           mov dl,0dh
           mov ah,2
           int 21h
           jmp loop1

routine_4: mov dl,52h
           mov ah,2
           int 21h
           mov dl,34h
           mov ah,2
           int 21h
           mov dl,0ah
           mov ah,2
           int 21h
           mov dl,0dh
           mov ah,2
           int 21h
           jmp loop1

routine_5: mov dl,52h
           mov ah,2
           int 21h
           mov dl,35h
           mov ah,2
           int 21h
           mov dl,0ah
           mov ah,2
           int 21h
           mov dl,0dh
           mov ah,2
           int 21h
           jmp loop1

exit:      mov ah,4ch
           int 21h

code       ends
           end  start