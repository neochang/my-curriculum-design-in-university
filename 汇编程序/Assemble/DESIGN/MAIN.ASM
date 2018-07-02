;MAIN.ASM--Main program--#
;  Program function:(1)Copy a file (2)Search a word in a file.
;    (3)Replace the word which has been found with another word given by the user.
;-------------------------
  INCLUDE  MACRO.MAC
;-------------------------
  extrn    copy:far,search:far
;-------------------------
  public   MESSG11
  public   MESSG12
  public   MESSG13
  public   MESSG14
  public   MESSG15
  public   MESSG16
  public   MESSG17
  public   MESSG18
  public   MESSG19
  public   MESSG24
  public   MESSG25
  public   MESSG26
  public   MESSG27
  public   MESSG28
  public   MESSG29
  public   MESSG30
  public   ERRMSG00
  public   ERRMSG02
  public   ERRMSG03
  public   ERRMSG04
  public   ERRMSG05
  public   ERRMSG06
  public   ERRMSG07
  public   ERRMSG08
  public   ERRMSG09
  public   ERRMSG10
  public   ERRMSG11
  public   ERRMSG12
  public   ERRMSG13
  public   ERRMSG14
  public   ERRMSG15
  public   ERRMSG16
  public   ANI01
  public   ANI02
  public   ANI03
  public   ANICOUNT
  public   sfile
  public   dfile
  public   shandle
  public   dhandle
  public   fbuffer
  public   srchmax
  public   srchact
  public   srchbuff
  public   srchcount
  public   replmax
  public   replact
  public   replbuff
;**********************************************        
  DATA       SEGMENT
;--------- Main user interface ------------>>>
     MESSG01    DB   80 dup('*'),'$'
     MESSG02    DB   80 dup('='),'$'
     MESSG03    DB   5 dup(' '),'This program can Copy a file or Search and Replace words in a file.',0DH,0AH,'$'
     MESSG04    DB   5 dup(' '),'Select a function by entering the number before it:',0DH,0AH,'$'
     MESSG05    DB   0DH,0AH,'$'
     MESSG06    DB   20 dup(' '),30 dup('-'),0DH,0AH,'$'
     MESSG07    DB   20 dup(' '),'1. COPY A FILE',0DH,0AH,'$'
     MESSG08    DB   20 dup(' '),'2. SEARCH AND REPLACE',0DH,0AH,'$'
     MESSG00    DB   20 dup(' '),'0. EXIT',0DH,0AH,'$'
     MESSG09    DB   20 dup(' '),30 dup('-'),0DH,0AH,'$'
     MESSG10    DB   40 dup(' '),'Your Selection is:','$'
;---------- UI of COPY -------------------------------------------------------->>>
     MESSG11    DB   30 dup(' '),'**** FILE  COPY ****',0DH,0AH,'$'
     MESSG12    DB   20 dup(' '),'SOURCE FILE NAME:','$'
     MESSG13    DB   20 dup(' '),'DESTINATION FILE NAME:','$'
     MESSG14    DB   40 dup(' '),'START COPY?(Y/N):','$'
;---------- UI OF SEARCH AND REPLACE------------------------------------------->>>
     MESSG15    DB   25 dup(' '),'**** FILE SEARCH AND REPLACE ****',0DH,0AH,'$'
     MESSG16    DB   20 dup(' '),'THE WORD YOU WANT TO FIND IS:','$'
     MESSG17    DB   20 dup(' '),'TOTALLY FOUND:','$'
     MESSG18    DB   20 dup(' '),'DO YOU WANT TO REPLACE?(Y/N):','$'
     MESSG19    DB   20 dup(' '),'REPLACE IT AS:','$'
     ;------------------------------------------------------
     MESSG20    DB   0DH,0AH,10 dup(' '),'Are you sure you want to Quit?(Y/N):','$'
     MESSG21    DB   0DH,0AH,10 dup(' '),'$'
     MESSG22    DB   'Thank you for your use! >>>>> BYE BYE! '
     COUNT      EQU  $-MESSG22
     MESSG23    DB   COUNT dup(' ')
     MESSG24    DB   20 dup(' '),'Copying....','$'
     MESSG25    DB   3 dup(0DH,0AH),10 dup(' '),'Successful!','$'
     MESSG26    DB   20 DUP(' '),'Checking for blanks....','$'
     MESSG27    DB   20 dup(' '),'There is no blank in the file!',0DH,0AH
                DB   20 dup(' '),'Press any key to continue...','$'
     MESSG28    DB   20 dup(' '),'Blanks found! Delete when copy?(Y/N):','$'
     MESSG29    DB   20 dup(' '),'Copying with blanks exclusive...','$'
     MESSG30    DB   20 dup(' '),'Replacing....','$'
     ANI01      DB   0DH,0AH,20 dup(' '),'$'
     ANI02      DB   '==================='
     NUM        EQU  $-ANI02
     ANI03      DB   NUM dup('>')
     ANICOUNT   DB   NUM           ;NUM不可声明为public,因为是常量，运行会出错
;-------------------------------------------------------------------------------
     ERRMSG01   DB   0DH,0AH,10 dup(' '),'Sorry,you have entered a WRONG number!!','$'
     ERRMSG02   DB   0DH,0AH,10 dup(' '),'Press any key to continue...','$'
     ERRMSG00   DB   0DH,0AH,20 dup(' '),'Press any key to continue...','$'
     ERRMSG03   DB   3 dup(0DH,0AH),10 dup(' '),'Creat file error!','$'
     ERRMSG04   DB   3 dup(0DH,0AH),10 dup(' '),'Open file error!','$'
     ERRMSG05   DB   3 dup(0DH,0AH),10 dup(' '),'Read file error!','$'
     ERRMSG06   DB   3 dup(0DH,0AH),10 dup(' '),'Write file error!','$'
     ERRMSG07   DB   3 dup(0DH,0AH),10 dup(' '),'Close source file error!','$'
     ERRMSG08   DB   3 dup(0DH,0AH),10 dup(' '),'Close destination file error!','$'
     ERRMSG09   DB   3 dup(0DH,0AH),10 dup(' '),'Delete error!','$'
     ERRMSG10   DB   3 dup(0DH,0AH),10 dup(' '),'Move file pointer error!','$'
     ERRMSG11   DB   20 dup(' '),'Destination file name cannot be empty!',0dh,0ah
                DB   20 dup(' '),'--------','$'
     ERRMSG12   DB   20 dup(' '),'Source file name cannot be empty!',0dh,0ah
                DB   20 dup(' '),'--------','$'
     ERRMSG13   DB   20 dup(' '),'Destination file already exists!',0dh,0ah
                DB   20 dup(' '),'--------','$'
     ERRMSG14   DB   20 dup(' '),'Search word cannot be empty!',0dh,0ah
                DB   20 dup(' '),'--------','$'
     ERRMSG15   DB   20 dup(' '),'Replace word cannot be empty!',0dh,0ah
                DB   20 dup(' '),'--------','$'
     ERRMSG16   DB   3 dup(0DH,0AH),10 dup(' ')
                DB   'Replace Failed!',0dh,0ah,0dh,0ah
                DB   10 dup(' '),'Sorry,Length of Replace word and Search word must be equal!','$'
;---------------------------------------------------------------------------------
     sfile      db   64               ;Store the ASCIZ string of source file.
                db   ?
                db   64 dup(' ')
     dfile      db   64               ;Store the ASCIZ string of destination file.
                db   ?
                db   64 dup(' ')
     shandle    dw   ?                ;Source file handle
     dhandle    dw   ?                ;Destination file handle
     fbuffer    db   256 dup(' ')     ;Buffer for reading file
     ;--------------------------
     srchmax    db   20               ;要查找的字符缓冲区
     srchact    db   ?
     srchbuff   db   20 dup(' ')
     srchcount  dw   0                ;查找记数器
     ;--------------------------
     replmax    db   20               ;要替换的字符缓冲区
     replact    db   ?
     replbuff   db   20 dup (' ')
;-------------------------------------------------------
  DATA       ENDS

;**********************************************************************************
  CODE       SEGMENT

      assume cs:code,ds:data
;--------------------------------------------------
  MAIN       PROC      FAR

  START:
             push     ds
             mov      ax,0
             push     ax

             mov      ax,data
             mov      ds,ax

  again:     cls                       ;Clear the screen and set cursor position.

             DISPLAY  MESSG01          ;Print the user interface
             DISPLAY  MESSG02
             drawCRLF
             DISPLAY  MESSG03
             DISPLAY  MESSG04
             DISPLAY  MESSG05
             DISPLAY  MESSG06
             DISPLAY  MESSG07
             DISPLAY  MESSG08
             DISPLAY  MESSG00
             DISPLAY  MESSG09
             drawCRLF
             DISPLAY  MESSG10
             
             input                    ;Accept input for function selection.
             cmp      al,31h          ;Is it '1'?
             je       lb_copy         ;  yes,Go to copy file
             cmp      al,32h          ;Is it '2'?
             je       lb_srch         ;  yes,Go to search file 
             cmp      al,30h          ;Is it '0'?
             je       lb_exit         ;  yes,Exit to DOS
             jmp      lb_resel        ;Print error message,and select again.
             
  lb_copy:   call     copy
             jmp      again
             
  lb_srch:   call     search
             jmp      again
             
  lb_resel:  cls
             drawCRLF
             drawCRLF
             display  ERRMSG01        ;Print error message
             display  ERRMSG02
             pause                    ;Wait for pressing any key.
             jmp      again
             
  lb_exit:   cls
             drawCRLF
             drawCRLF
             display  MESSG20
             input
             cmp      al,'Y'
             je       exit
             cmp      al,'y'
             je       exit
             cmp      al,'N'
             je       jump
             cmp      al,'n'
             je       jump
             jmp      lb_exit
     jump:   jmp      near ptr again  ;If use "je again" directly,
                                      ;   Jump out of range
                                      
                                      
     exit:   cls                      ;Clear screen
             hidecur                  ;Hide the cursor
             drawCRLF
             drawCRLF
             display  MESSG21
             mov      cx,count
             lea      si,MESSG22      ;display quit message
 next_char1: output   [si]
             inc      si
             waitf                    ;Delay a little while
             loop     next_char1
             
             readcur                  ;Read the cursor position
             sub      dl,count        ;Set cursor to the beginning of quit message
             mov      al,dh           ;Row to AL
             mov      bl,dl           ;Column to BL
             setcur   al,bl           ;Set cursor position
             mov      cx,count
             lea      si,MESSG23      ;display blank
 next_char2: output   [si]
             inc      si
             waitf
             loop     next_char2
             qcls
             RET
             
  MAIN       ENDP
;--------------------------------------------------
  CODE       ENDS
;--------------------------------------------------
             END      START