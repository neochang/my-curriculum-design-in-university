
DATA  SEGMENT
NUM DW 76,69,84,90,73,88,99,63,100,80        ;The students scores
S6  DW 0
S7  DW 0
S8  DW 0
S9  DW 0
S10 DW 0
DATA ENDS

CODE  SEGMENT
MAIN PROC FAR      
      ASSUME CS:CODE,DS:DATA
START: PUSH DS                               ;Save data for return
       MOV AX,0
       PUSH AX

       MOV AX,DATA
       MOV DS,AX

       MOV CX,10             ;Set counter to 10
       CALL COUNT
       RET
MAIN ENDP


COUNT PROC NEAR
      MOV SI,0
NEXT: MOV AX,NUM[SI]        ; Read the first score
      MOV BX,10
      DIV BL                ; AX/BL,the quotient is put into AL.
      MOV BL,AL             ; Move the quotient from AL to BL
      CBW                   ;   and extend it to Word.
      SUB BX,6
      SAL BX,1
      INC S6[BX]
      ADD SI,2              ; Read the next score
      LOOP NEXT
      RET
COUNT ENDP
CODE ENDS     
      END START

