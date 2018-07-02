;SEARCH.ASM----Search Module----#
;   This Module implements the function of Searching files.
;************************************************
  include   MACRO.MAC
;----------------------
  extrn     MESSG12:byte
  extrn     MESSG15:byte
  extrn     MESSG16:byte
  extrn     MESSG17:byte
  extrn     MESSG18:byte
  extrn     MESSG19:byte
  extrn     ERRMSG00:byte
  extrn     ERRMSG02:byte
  extrn     ERRMSG04:byte
  extrn     ERRMSG05:byte
  extrn     ERRMSG10:byte
  extrn     ERRMSG14:byte
  extrn     ERRMSG12:byte
  extrn     sfile:byte
  extrn     shandle:word
  extrn     fbuffer:byte 
  extrn     srchmax:byte
  extrn     srchact:byte
  extrn     srchbuff:byte
  extrn     srchcount:word
  extrn     replace:far
;----------------------
; Public variable and procedure declarations:

  public  search
;************************************************
  code_search   segment

           assume  cs:code_search
;----------------------------------(1)
  search     proc    far

             cls
             drawCRLF                     ;Draw the user interface
             drawCRLF
             display    MESSG15
             drawCRLF
   request3: drawCRLF
             display    MESSG16
             readname   srchmax          ;输入要查找的字符串
             cmp        srchbuff,0dh     ;未输入?
             jne        proceed3
             drawCRLF
             drawCRLF
             display    ERRMSG14
             jmp        request3
             
   proceed3: drawCRLF
   request4: drawCRLF
             display    MESSG12
             readname   sfile
             cmp        sfile+2,0dh     ;用户缺省要查找的文件名?
             jne        proceed4        ;否,继续
             drawCRLF
             drawCRLF
             display    ERRMSG12
             jmp        request4
             
   proceed4: mov        cl,sfile+1      ;Get source file name length
             xor        ch,ch
             mov        si,cx
             mov        [si+sfile+2],0  ;Add 0 to the end,form ASCIZ
             mov        ah,3dh          ;Open source file
             mov        al,0            ;Open for read
             lea        dx,sfile+2
             int        21h
             mov        bx,ax           ;Source file handle to BX,get ready to read
             jc         erra
             mov        shandle,ax
             
             ;***** 查找部分 *****>>>
             mov        srchcount,0     ;记数器清零
     not_eq: mov        si,0            ;si作偏移地址
             mov        di,0            ;di记录比较了几个字符
             mov        cl,srchact      ;要比较的字符实际长度放入BP
             mov        ch,0
             mov        bp,cx
   cmp_next: mov        cx,1            ;read length
             mov        ah,3fh
             lea        dx,fbuffer
             int        21h
             jc         errb
             cmp        ax,0            ;AX=0? end of file
             je         jump15          ;  exit,比较完毕>>>
             mov        dl,srchbuff[si]
             cmp        dl,fbuffer      ;比较字符是否相等
             je         eql             ;相等，跳转到eql
             cmp        di,0            ;di 为0，不用回溯文件指针
             je         not_eq
             mov        ah,42h          ;Request move pointer
             mov        al,1            ;不相等，将文件指针回退di字节即可
             mov        cx,0ffffh
             neg        di              ;取负di,指针回退
             mov        dx,di
             int        21h
             jc         errc
             jmp        not_eq
        eql: inc        si              ;相等
             inc        di
             dec        bp
             jnz        cmp_next
             inc        srchcount       ;一次loop之后，证明找到一个匹配的
             jmp        not_eq          ;查找是否还有匹配的
             ;***** 查找部分 *****<<<
             
     jump15: jmp       near ptr srch_end 
             
       erra: cls                        ;Open error
             display    ERRMSG04
             display    ERRMSG02
             mov        ah,3eh
             int        21h
             pause
             ret
             
       errb: cls                        ;Read error
             display    ERRMSG05
             display    ERRMSG02
             mov        ah,3eh
             int        21h
             pause
             ret
             
       errc: cls
             display    ERRMSG10
             display    ERRMSG02
             mov        ah,3eh          ;Move pointer error,Close file
             int        21h
             pause
             ret
             
   srch_end: mov        ah,3eh           ;比较完毕，正常关闭文件
             int        21h
             drawCRLF
             drawCRLF
             display    MESSG17           ;输出统计结果
             mov        bx,srchcount
             mov        cx,10000d         ;divide by 10000
             call       dec_div
             mov        cx,1000d          ;divide by 1000
             call       dec_div
             mov        cx,100d           ;divide by 100
             call       dec_div
             mov        cx,10d            ;divide by 10
             call       dec_div
             mov        cx,1d             ;divide by 1
             call       dec_div
             
             cmp        srchcount,0       ;若为0，则不再询问是否替换
             jne        ask
             drawCRLF
             display    ERRMSG00
             pause
             ret
                      
        ask: drawCRLF
             drawCRLF
             display    MESSG18           ;询问是否进行替换
      inpt2: input
             cmp        al,'Y'
             je         replc
             cmp        al,'y'
             je         replc
             cmp        al,'N'
             je         return
             cmp        al,'n'
             je         return
             jmp        inpt2
             
     return: ret
     
      replc: call       replace           ;调用replace进行替换
             ret
             
  search     endp
;-----------------------------------(2)
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
        mov   ah,02                        ;display function
        int   21h                          ;call DOS
        ret                                ;return from dec_div

  dec_div   endp
;---------------------------------------------
  code_search   ends
;================================================
                end 