;HEXSUB--Main Program--#
;  read two hex on keyboard, subtract them 
;     and convert the result to dec on screen

;EQU STATEMENTS GOES HERE

display    equ   2h         ;video output
key_in     equ   1h         ;keyboard input
doscall    equ   21h        ;DOS interrupt number

;***********************************************
data    segment                            ;define data segment
  
   minuend       dw   ?
   subtrahend    dw   ?
   result        dw   ?
   r_flag        db   0                    ;Mark whether the result is negative
   messg1        db   'Please input the first HEX number(A to F must be CAPS):',0ah,0dh,'$'
   messg2        db   'Please input the second HEX number(A to F must be CAPS):',0ah,0dh,'$'
   messg3        db   'The result is:',0ah,0dh,'$'

data    ends

;***********************************************
code    segment                          ;define code segment
;-----------------------------------------------(1)
main    proc    far                      ;main part of program

   assume cs:code,ds:data

 start:
        push  ds                         ;save old data segment
        sub   ax,ax                      ;put zero in AX
        push  ax

        mov   ax,data
        mov   ds,ax

;MAIN PART OF PROGRAM GOES HERE

        mov   ah,06                      ;Clear the screen
        mov   al,0
        mov   ch,0
        mov   cl,0
        mov   dh,24
        mov   dl,79
        mov   bh,0fh
        int   10h

        mov   ah,02                      ;Set cursor position
        mov   bh,0
        mov   dh,0
        mov   dl,0
        int   10h

        mov   ah,09                      ;display prompt
        lea   dx,messg1
        int   21h

        call  hexibin                    ;keyboard to binary,the first number
        mov   minuend,bx

        call  crlf                       ;print CR & LF

        mov   ah,09                      ;display prompt
        lea   dx,messg2
        int   21h

        call  hexibin                    ;keyboard to binary,the second number
        mov   subtrahend,bx

        call  subtract                   ;subtract the two numbers
        call  crlf

        mov   ah,09                      ;display prompt
        lea   dx,messg3
        int   21h

        mov   bx,result                  ;move the result to bx
        call  binidec                    ;  so as to convert binary to decimal
        call  crlf

        ret                              ;return to DOS

main    endp
;-----------------------------------------------(2)
hexibin   proc   near                    ;define subprocedure

;Subroutine to convert hex on keyboard to
;  binary. Result is left in BX register.

        mov   bx,0                       ;clear BX for number
        mov   si,4                       ;set si for exit flag

;Get digit form keyboard,convert to binary

 newchar:
        mov   ah,key_in                  ;keyboard input
        int   doscall                    ;call DOS
        sub   al,30h                     ;ASCII to binary
        jl    exit                       ;exit if <0
        cmp   al,10d                      ;is it >9d ?
        jl    add_to                     ;no,so it's digit
;not digit(0 to 9),may be letter (a to f)
        sub   al,7h                      ;convert ASCII to binary
        cmp   al,0ah                     ;is it <0a hex?
        jl    exit                       ;yes,not letter
        cmp   al,10h                     ;is it >0f hex?
        jge   exit                       ;yes,not letter
;is hex digit,add to number in BX
 add_to:
        mov   cl,4                       ;set shift count
        shl   bx,cl                      ;rotate BX 4 bits to receive new number
        mov   ah,0                       ;zero out AH
        add   bx,ax                      ;add digit to number
        dec   si                         ;already 4 numbers?
        jz    exit                       ;yes,stop input
        jmp   newchar                    ;get next digit
 exit:
        ret                              ;return from hexibin

hexibin   endp
;-----------------------------------------------(3)
subtract  proc  near

;Subtract the two opetators,and
;  put the result into "result" in data segment

        mov   bx,minuend
        mov   ax,subtrahend
        cmp   bx,ax
        jae   go_on
        xchg  bx,ax                      ;exchange two operator
        mov   r_flag,1                   ;the result is negative
 go_on: sub   bx,ax
        mov   result,bx
        ret                              ;return from subtract

subtract  endp
;-----------------------------------------------(4)
binidec   proc  near

;Subroutine to convert binary number in BX
;  to decimal on console screen

        cmp   r_flag,1
        jne   print
        mov   dl,2dh                       ;display "-"
        mov   ah,display
        int   doscall

 print: mov   cx,10000d                    ;divide by 10000
        call  dec_div
        mov   cx,1000d                     ;divide by 1000
        call  dec_div
        mov   cx,100d                      ;divide by 100
        call  dec_div
        mov   cx,10d                       ;divide by 10
        call  dec_div
        mov   cx,1d                        ;divide by 1
        call  dec_div
        ret                                ;return from binidec

binidec   endp
;-----------------------------------------------(5)
dec_div   proc  near

;Subroutine to divide number in BX by number in CX
;print quotient on screen
;(dividend in DX+AX,
;   divisor in CX,
;       remainder in DX,
;            quotient in AX(AL)

        mov   ax,bx                        ;number low half
        mov   dx,0                         ;zero out high half
        div   cx                           ;divide by CX
        mov   bx,dx                        ;remainder into BX
        mov   dl,al                        ;quotient into DL
;print the contents of DL on screen
        add   dl,30h                       ;convert to ASCII
        mov   ah,display                   ;display function
        int   doscall                      ;call DOS
        ret                                ;return from dec_div

dec_div   endp
;-----------------------------------------------(6)
crlf      proc  near

;print carriage return and linefeed

        mov   dl,0ah                       ;linefeed
        mov   ah,display                   ;display function
        int   doscall                      ;call DOS

        mov   dl,0dh                       ;carriage return
        mov   ah,display                   ;display function
        int   doscall                      ;call DOS
        ret                                ;return from crlf

crlf      endp
;-----------------------------------------------
code      ends                             ;end of code segment
;***********************************************
          end  start                       ;end of assembly
