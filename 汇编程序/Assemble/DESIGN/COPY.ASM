;COPY.ASM----Copy Module----#
;   This Module implements the function of COPYing files.
;************************************************
  include   MACRO.MAC
;----------------------
  extrn     MESSG11:byte
  extrn     MESSG12:byte
  extrn     MESSG13:byte
  extrn     MESSG14:byte
  extrn     MESSG24:byte
  extrn     MESSG25:byte
  extrn     MESSG26:byte
  extrn     MESSG27:byte
  extrn     MESSG28:byte
  extrn     MESSG29:byte
  extrn     ANI01:byte
  extrn     ANI02:byte
  extrn     ANI03:byte
  extrn     ANICOUNT:byte
  extrn     ERRMSG02:byte
  extrn     ERRMSG03:byte
  extrn     ERRMSG04:byte
  extrn     ERRMSG05:byte
  extrn     ERRMSG06:byte
  extrn     ERRMSG07:byte
  extrn     ERRMSG08:byte
  extrn     ERRMSG09:byte
  extrn     ERRMSG10:byte
  extrn     ERRMSG11:byte
  extrn     ERRMSG12:byte
  extrn     ERRMSG13:byte
  extrn     sfile:byte
  extrn     dfile:byte
  extrn     shandle:word
  extrn     dhandle:word
  extrn     fbuffer:byte
;----------------------
; Public variable and procedure declarations:

  public  copy
;************************************************
  code_copy     segment

           assume  cs:code_copy
;----------------------------------(1)
  copy       proc    far
                          
             cls
             drawCRLF                    ;Draw the user interface
             drawCRLF
             display    MESSG11
             drawCRLF
   request1: drawCRLF
             display    MESSG12
             readname   sfile            ;Read source file name
             cmp        sfile+2,0dh      ;用户缺省源文件名?
             jne        proceed1         ;否,继续
             drawCRLF                    ;是,要求重新输入
             drawCRLF
             display    ERRMSG12
             jmp        request1
   proceed1: mov        cl,sfile+1       ;Get source file name length
             xor        ch,ch
             mov        si,cx
             mov        [si+sfile+2],0   ;Add 0 to the end,form ASCIZ
             
             drawCRLF
   request2: drawCRLF
             display    MESSG13
             readname   dfile            ;Read destination file name
             cmp        dfile+2,0dh      ;用户缺省目的文件名?
             jne        proceed2         ;否,继续
             drawCRLF                    ;是,要求重新输入
             drawCRLF
             display    ERRMSG11
             jmp        request2
   proceed2: mov        cl,dfile+1
             xor        ch,ch
             mov        si,cx
             mov        [si+dfile+2],0
             
             mov        ah,3dh          ;尝试打开目的文件,若可以,证明重名
             mov        al,0            ;Open for read
             lea        dx,dfile+2
             int        21h
             jc         proceed3        ;打开失败,未重名
             drawCRLF                   ;打开成功,重名
             drawCRLF
             display    ERRMSG13
             mov        bx,ax
             mov        ah,3eh
             int        21h
             jmp        request2
             
   proceed3: drawCRLF
             drawCRLF
             display    MESSG14
     inpt:   input                       ;confirm copy
             cmp        al,'Y'
             je         startcp
             cmp        al,'y'
             je         startcp
             cmp        al,'N'
             je         exit0
             cmp        al,'n'
             je         exit0
             jmp        inpt
             
  startcp:   call chk_blank             ;Check for blanks

    exit0:   ret                        ;return to main proc
    
  copy       endp
;-----------------------------------(2)
  chk_blank      proc     near

; This procedure check the file to see
;   if there is any blank.

             drawCRLF
             drawCRLF
             display    MESSG26
             mov        ah,3dh          ;Open source file
             mov        al,2            ;Open for read and write
             lea        dx,sfile+2
             int        21h
             mov        bx,ax           ;Source file handle to BX,get ready to read
             jc         jump13          ;Open error
             mov        shandle,ax

     rdnext: mov        cx,1            ;read 1 byte per time
             mov        ah,3fh
             lea        dx,fbuffer
             int        21h
             jc         jump8
             cmp        ax,0            ;AX=0? end of file
             je         jump7           ;  Exit chk_blank procedure
             cmp        fbuffer,20h     ;is it blank?
             je         querry          ;delete blank
             jmp        rdnext

      jump7: jmp        near ptr chk_end
      jump8: jmp        near ptr err02
     jump13: jmp        near ptr err01

     querry: drawCRLF
             drawCRLF
             display    MESSG28
      inpt1: input
             cmp        al,'Y'
             je         del
             cmp        al,'y'
             je         del
             cmp        al,'N'
             je         ndel
             cmp        al,'n'
             je         ndel
             jmp        inpt1

       ndel: call       ndel_copy
             ret

        del: call       del_copy
             ret

      err01: cls
             display    ERRMSG04
             display    ERRMSG02
             mov        ah,3eh          ;Open error,Close file
             int        21h
             pause
             ret

      err02: cls
             display    ERRMSG05
             display    ERRMSG02
             mov        ah,3eh          ;Read error,Close file
             int        21h
             pause
             ret

    chk_end: drawCRLF
             drawCRLF
             display    MESSG27
             pause
             call       ndel_copy
             ret

  chk_blank      endp
;------------------------------------(3)
  ndel_copy      proc    near               
  
  ;本子程序复制时不删除空格
  
             drawCRLF
             drawCRLF
             display    MESSG24
             animate    ANI01,ANI02,ANICOUNT,ANI03
             mov        ah,3ch          ;Create distination file
             lea        dx,dfile+2      ;DS:DX point to ASCIZ
             mov        cx,0000h        ;Normal file
             int        21h
             mov        bx,ax           ;File handle to BX
             jc         jump1           ;CF=1,Create failed
             mov        dhandle,ax
             
             mov        bx,shandle      ;将源文件代号放入BX
             mov        ah,42h          ;Move pointer to the
             mov        al,00           ;  beginning
             mov        cx,00
             mov        dx,00
             int        21h
             
       r_w:  mov        cx,256          ;read length
             mov        ah,3fh
             lea        dx,fbuffer
             int        21h
             jc         jump3
             cmp        ax,0            ;AX=0? end of file
             je         exit            ;  exit
             
             mov        cx,ax           ;length actually read
             mov        ah,40h          ;Write to file
             lea        dx,fbuffer
             mov        bx,dhandle
             int        21h
             jc         jump4
             mov        bx,shandle      ;Write OK,source file handle to BX
             jmp        r_w
             
    ;Jump list,to avoid jump range out.
    jump1:   jmp        near ptr crt_err
    jump3:   jmp        near ptr rd_err
    jump4:   jmp        near ptr wt_err
    jump5:   jmp        near ptr close_serr
    jump6:   jmp        near ptr close_derr
             
     exit:   mov        bx,shandle      ;Normally close file
             mov        ah,3eh
             int        21h
             jc         jump5
             mov        bx,dhandle
             mov        ah,3eh
             int        21h
             jc         jump6
             cls
             display    MESSG25         ;复制成功
             display    ERRMSG02
             pause       
             ret
             
    crt_err: cls
             display    ERRMSG03
             display    ERRMSG02
             mov        ah,3eh
             int        21h
             pause
             ret
             
     rd_err: cls
             display    ERRMSG05
             display    ERRMSG02
             mov        ah,3eh
             int        21h
             pause
             ret
             
     wt_err: cls
             display    ERRMSG06
             display    ERRMSG02
             mov        ah,3eh
             int        21h
             pause
             ret
             
 close_serr: cls
             display    ERRMSG07
             display    ERRMSG02
             mov        ah,3eh
             int        21h
             pause
             ret
             
 close_derr: cls
             display    ERRMSG08
             display    ERRMSG02
             mov        ah,3eh
             int        21h
             pause
             ret
             
 ndel_copy       endp
;-----------------------------------(4)
  del_copy       proc   near
  
  ;本子程序复制时跳过空格
  
             drawCRLF
             drawCRLF
             display    MESSG29
             animate    ANI01,ANI02,ANICOUNT,ANI03
             mov        ah,3ch          ;Create distination file
             lea        dx,dfile+2      ;DS:DX point to ASCIZ
             mov        cx,0000h        ;Normal file
             int        21h
             mov        bx,ax           ;File handle to BX
             jc         jump2           ;Create error
             mov        dhandle,ax
             
             mov        bx,shandle      ;将源文件代号放入BX
             mov        ah,42h          ;Move pointer to the
             mov        al,00           ;  beginning 
             mov        cx,00
             mov        dx,00
             int        21h
             jc         jump11
             
    rdnext2: mov        cx,1            ;read 1 byte per time
             mov        ah,3fh
             lea        dx,fbuffer
             int        21h
             jc         jump9
             cmp        ax,0            ;AX=0? end of file
             je         jump10          ;  Exit del_blank procedure
             
             cmp        fbuffer,20h     ;如果是空格，则跳过不写
             jne        dirct_wr
             jmp        rdnext2         ;跳过空格后，继续读下一字节
             
   dirct_wr: mov        cx,1
             mov        ah,40h          ;Write to file
             mov        bx,dhandle
             lea        dx,fbuffer
             int        21h
             jc         jump12
             mov        bx,shandle      ;Write OK,source file handle to BX
             jmp        rdnext2

      jump2: jmp        near ptr err03
      jump9: jmp        near ptr err04
     jump10: jmp        near ptr exit00
     jump11: jmp        near ptr err05
     jump12: jmp        near ptr err06

      err03: cls
             display    ERRMSG03       ;Create error
             display    ERRMSG02
             mov        ah,3eh
             int        21h
             pause
             ret
             
      err04: cls
             display    ERRMSG05
             display    ERRMSG02
             mov        ah,3eh          ;Read error,Close file
             int        21h
             pause
             ret
             
      err05: cls
             display    ERRMSG10
             display    ERRMSG02
             mov        ah,3eh          ;Move pointer error,Close file
             int        21h
             pause
             ret
             
      err06: cls
             display    ERRMSG06        ;Write error,Close file
             display    ERRMSG02
             mov        ah,3eh
             int        21h
             pause
             ret
             
    cl_serr: cls
             display    ERRMSG07
             display    ERRMSG02
             mov        ah,3eh
             int        21h
             pause
             ret
             
    cl_derr: cls
             display    ERRMSG08
             display    ERRMSG02
             mov        ah,3eh
             int        21h
             pause
             ret

    exit00:  mov        bx,shandle      ;Normally close file
             mov        ah,3eh
             int        21h
             jc         cl_serr
             mov        bx,dhandle
             mov        ah,3eh
             int        21h
             jc         cl_derr
             cls
             display    MESSG25         ;复制成功
             display    ERRMSG02
             pause       
             ret
   
  del_copy       endp
;-----------------------------------
  code_copy      ends
;================================================
                 end  
