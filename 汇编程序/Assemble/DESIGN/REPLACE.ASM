;REPLACE.ASM----Replace Module----#
;   This Module implements the function of Replacing word in files.
;************************************************
  include   MACRO.MAC
;----------------------
  extrn     MESSG19:byte
  extrn     MESSG25:byte
  extrn     MESSG30:byte
  extrn     ERRMSG02:byte
  extrn     ERRMSG04:byte
  extrn     ERRMSG05:byte
  extrn     ERRMSG06:byte
  extrn     ERRMSG10:byte
  extrn     ERRMSG15:byte
  extrn     ERRMSG16:byte
  extrn     ANI01:byte
  extrn     ANI02:byte
  extrn     ANI03:byte
  extrn     ANICOUNT:byte
  extrn     sfile:byte
  extrn     shandle:word
  extrn     fbuffer:byte
  extrn     srchact:byte
  extrn     srchbuff:byte
  extrn     replmax:byte
  extrn     replact:byte
  extrn     replbuff:byte
;----------------------
; Public variable and procedure declarations:

  public  replace
;************************************************
  code_replace   segment

           assume  cs:code_replace
;----------------------------------(1)
  replace    proc    far
  
             drawCRLF
   request5: drawCRLF
             display    MESSG19
             readname   replmax          ;输入要替换成的字符串
             cmp        replbuff,0dh     ;未输入?
             jne        proceed5
             drawCRLF
             drawCRLF
             display    ERRMSG15
             jmp        request5
             
   proceed5: drawCRLF
             drawCRLF
             display    MESSG30
             animate    ANI01,ANI02,ANICOUNT,ANI03
             mov        ah,3dh          ;Open source file
             mov        al,2            ;Open for read and write
             lea        dx,sfile+2      ;文件名在search子程序中已处理
             int        21h
             mov        bx,ax           ;Source file handle to BX,get ready to read
             jc         erri
             mov        shandle,ax
             
             mov        al,srchact
             cmp        replact,al
             ja         long_rep        ;判断替换串与源串的长度
             jb         short_rep
             jmp        equal_rep
             
   long_rep: call       long_replace
             ret
             
  short_rep: call       short_replace
             ret
             
  equal_rep: call       equal_replace
             ret
             
       erri: cls                        ;Open error
             display    ERRMSG04
             display    ERRMSG02
             mov        ah,3eh
             int        21h
             pause
             ret
             
  replace       endp
;-----------------------------------------(2)
  long_replace  proc   near
  
; 此子程序完成替换串比查找串长度长时的替换功能。 
; 此子程序的功能并未实现，因而只给出了错误信息。也就是说，目前
; 在进行字符串替换时，只能替换和原来查找的字符串等长的字符。
; 但已经考虑可以采用如下算法：(1)用equal_replace中的查找方法
; 进行查找，找到匹配的字符串.(2)读出紧邻匹配串之后 replact-srchact
; (即:替换串长度-源串长度) 长度的文件内容至PreBuffer中,再继续读出
; replact-srchact长度的文件内容到CurBuffer中,(3)将PreBuffer中的内
; 容写入到文件中CurBuffer所在的位置，将CurBuffer内容传给PreBuffer
; (4)再读出replact-srchact长度的内容到CurBuffer，重复(3)、(4)两步
; 即可将匹配串以后的内容均后移replact-srchact字节，从而可以将替换串
; 写入到原来查找串的位置。
             
             cls
             display    ERRMSG16
             drawCRLF
             display    ERRMSG02
             pause
             ret
                
  long_replace  endp
;-----------------------------------------(3)
  short_replace  proc   near
  
; 此子程序完成替换串比查找串长度长时的替换功能。
; 此子程序的功能也尚未实现，只给出了错误信息。可以用删除数组
; 内容的算法将文件中匹配串之后的内容前移紧缩。但是有一个问题
; 尚未解决：数组删除之后只要将标志其长度的单元(通常是0号单元)
; 减一即可，但目前尚未查到能改变文件长度或从文件中将内容删除
; 的功能调用，故此子程序功能暂时无法实现。
  
             cls
             display    ERRMSG16
             drawCRLF
             display    ERRMSG02
             pause
             ret
                
  short_replace  endp
;-----------------------------------------(4)
  equal_replace  proc   near
  
    not_eq2: mov        si,0            ;si作偏移地址
             mov        di,0            ;di记录比较了几个字符
             mov        cl,srchact      ;要比较的字符实际长度放入BP
             mov        ch,0
             mov        bp,cx
  cmp_next2: mov        cx,1            ;read length
             mov        ah,3fh
             lea        dx,fbuffer
             int        21h
             jc         errii
             cmp        ax,0            ;AX=0? end of file
             je         jump16          ;  exit,替换完毕>>>
             mov        dl,srchbuff[si]
             cmp        dl,fbuffer      ;比较字符是否相等
             je         eql2            ;相等，跳转到eql
             cmp        di,0            ;di 为0，不用回溯文件指针
             je         not_eq2
             mov        ah,42h          ;Request move pointer
             mov        al,1            ;不相等，将文件指针回退di字节即可
             mov        cx,0ffffh
             neg        di              ;取负di,指针回退
             mov        dx,di
             int        21h
             jc         erriii
             jmp        not_eq2
       eql2: inc        si              ;相等
             inc        di
             dec        bp
             jnz        cmp_next2       ;一次loop之后，证明找到一个匹配的
             ;--- Begin to write ---
             mov        ah,42h          ;Request move pointer
             mov        al,1
             mov        cx,0ffffh
             neg        di              ;取负di,指针回退到要替换字符的开始
             mov        dx,di
             int        21h
             jc         erriii
             mov        ah,40h          ;进行替换
             lea        dx,replbuff
             mov        cl,replact      ;将字符串长度放入CX，即一次要写的长度
             mov        ch,0            
             int        21h
             jc         erriv           ;写入错误
             jmp        not_eq2         ;查找是否还有匹配的
             
     jump16: jmp       near ptr repl_end
             
      errii: cls                        ;Read error
             display    ERRMSG05
             display    ERRMSG02
             mov        ah,3eh
             int        21h
             pause
             ret
             
     erriii: cls
             display    ERRMSG10
             display    ERRMSG02
             mov        ah,3eh          ;Move pointer error,Close file
             int        21h
             pause
             ret
             
      erriv: cls                        ;Write error
             display    ERRMSG06
             display    ERRMSG02
             mov        ah,3eh
             int        21h
             pause
             ret
             
   repl_end: mov        ah,3eh           ;替换完毕，正常关闭文件
             int        21h
             cls
             display    MESSG25
             display    ERRMSG02
             pause
             ret
             
  equal_replace  endp
;-----------------------------------------
  code_replace   ends
;================================================
                end 