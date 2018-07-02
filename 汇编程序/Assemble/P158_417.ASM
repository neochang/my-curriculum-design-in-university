;**********************
d_seg  segment
  cwgw	 label	word
  augend dd     99251
  sum    dw     2 dup(?)
d_seg ends
;**********************
e_seg  segment
  addw   label  word
  addend dd     -15962
e_seg  ends
;**********************
c_seg  segment
  assume cs:c_seg,ds:d_seg,es:e_seg
main  proc far

start: push ds
       mov  ax,0
       push ax

      mov  ax,d_seg
      mov  ds,ax
      mov  ax,e_seg
      mov  es,ax

      mov  ax,cwgw
      mov  bx,cwgw+2
      add  ax,es:addw
      adc  bx,es:addw+2
      mov  sum,ax
      mov  sum+2,bx
      
      mov  AH,4ch
      int  21h
main   endp
c_seg  ends
       end start