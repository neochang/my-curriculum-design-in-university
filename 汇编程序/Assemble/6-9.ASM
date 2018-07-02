;*******************************
DATA  SEGMENT
  INBUF    LABEL  BYTE        ; name/phone parameter list
  MAXLEN   DB     21          ; max. name length
  BUFLEN   DB     ?           ; no.  chars entered
  INBUFFLD DB     21 DUP(?)   ; name/phone
  CRLF     DB     0DH,0AH,'$' 
  MESSG1   DB     'PLEASE INPUT NAME:','$'
  MESSG2   DB     'PLEASE INPUT A TELEPHONE NUMBER:','$'
  MESSG3   DB     'NAME                 TEL.','$'
  OUTNAME  DB     21 DUP(' ')
  OUTPHONE DB     21 DUP(' ')
  OUTBUF   DB     21 DUP(?),'$'
DATA  ENDS
;*******************************

;********************************
CODE  SEGMENT
     ASSUME CS:CODE,DS:DATA,ES:DATA
;------------------
MAIN  PROC  FAR

 START:  
     PUSH DS
     SUB  AX,AX
     PUSH AX

     MOV  AX,DATA
     MOV  DS,AX
     MOV  ES,AX       ; The destination opetator of "MOVSB" must use ES.

     MOV  AH,09       ; Display prompt message. 
     LEA  DX,MESSG1
     INT  21H
     MOV  AH,09
     LEA  DX,CRLF
     INT  21H
     CALL INPUT_NAME
   
     MOV  AH,09
     LEA  DX,MESSG2
     INT  21H
     MOV  AH,09
     LEA  DX,CRLF
     INT  21H
     CALL INPHONE

     CALL PRINTLINE
     RET

MAIN  ENDP

;-------------------
GETCHAR PROC NEAR

         MOV  AH,0AH
         LEA  DX,INBUF
         INT  21H
    
         MOV  BH,0               ; Clear chars after name
         MOV  BL,BUFLEN          ; Get count of chars
         MOV  CX,21
         SUB  CX,BX              ; Calc remaining length           
     LP1:MOV  INBUFFLD[BX],20H   ; set to blank
         INC  BX
         LOOP LP1

         MOV  AH,09              ; Print CR-LF
         LEA  DX,CRLF
         INT  21H
         RET

GETCHAR ENDP

;-------------------
INPUT_NAME PROC NEAR
         
         CALL GETCHAR
         CLD
         LEA  SI,INBUFFLD        ; Mov name from
         LEA  DI,OUTNAME         ;  INBUFFLD
         MOV  CX,21              ;     to OUTNAME
         REP  MOVSB
         RET

INPUT_NAME ENDP 

;------------------
INPHONE PROC NEAR

        CALL GETCHAR
        CLD
        LEA  SI,INBUFFLD        ; Mov phone number from
        LEA  DI,OUTPHONE        ;  INBUFFLD
        MOV  CX,21              ;     to OUTPHONE
        REP  MOVSB
        RET

INPHONE ENDP

;------------------
PRINTLINE PROC NEAR

        MOV  AH,09               ; Display prompt
        LEA  DX,MESSG3
        INT  21H
        MOV  AH,09
        LEA  DX,CRLF
        INT  21H

        LEA  SI,OUTNAME          ;Because OUTNAME and OUTPHONE does not
        LEA  DI,OUTBUF           ;  end with '$', cannot be displayed by
        CLD                      ;    09.
        MOV  CX,21
        REP  MOVSB
        MOV  AH,09               ; Display name
        LEA  DX,OUTBUF
        INT  21H

        LEA  SI,OUTPHONE         ; Display phone number
        LEA  DI,OUTBUF
        CLD
        MOV  CX,21
        REP  MOVSB
        MOV  AH,09
        LEA  DX,OUTBUF
        INT  21H

        MOV  AH,09
        LEA  DX,CRLF
        INT  21H
        RET

PRINTLINE ENDP 
     
;-------------------
CODE  ENDS
      END  START 
;********************************   