;PROGRAM TITLE GOES HERE--ex_movs
;****************************************************
data  segment                    ;define data segment
   source_buffer   db   40 dup('a')
data  ends
;****************************************************
extra segment                    ;define extra segment
   dest_buffer     db   40 dup(?)
extra ends
;****************************************************
code  segment                    ;define code segment
;----------------------------------------------------
main  proc    far                ;main part of program
    assume cs:code,ds:data,cs:extra
start:                           ;starting execution address
;set up stack for return
      push    ds                 ;save old data segment
      sub     ax,ax              ;put zero in AX
      push    ax                 ;save it on stack
;set DS register to current data segment
      mov     ax,data            ;data segment addr
      mov     ds,ax              ;  into ES register
;set ES register to current extra segment
      mov     ax,extra           ;extra segment addr
      mov     es,ax              ;  into ES register
;MAIN PART OF PROGRAM GOES HERE
      lea     si,source_buffer   ;put offset addr of source
                                 ;  buffer in SI
      lea     di,dest_buffer     ;put offset addr of dest
                                 ;  buffer in DI
      cld                        ;set DF flag to forward
      mov     cx,40              ;put count in CX
      rep     movsb              ;move entire string
      ret                        ;return to DOS
main  endp                       ;end of main part of program
;----------------------------------------------------
code  ends                       ;end of code segment
;****************************************************
      end     start              ;end of assembly