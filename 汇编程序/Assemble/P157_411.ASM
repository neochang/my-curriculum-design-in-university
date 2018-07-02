data_seg   segment
db       5                           ;计数值
data_list  dw   -1,0,2,5,4,5 dup(?)  ;10个字的数组
max        dw   ?                    ;存最大值
min        dw   ?                    ;存最小值
data_seg  ends

code       segment
   assume cs:code,ds:data_seg
start:
mov   ax,data_seg
mov   ds,ax
mov   cl,byte   ptr  data_list-1
mov   ch,0                           ;CX是计数器，初值5
mov   si,offset data_list
mov   ax,[si]                        ;取第一个数
mov   max,ax   
mov   min,ax                         ;做为最大、最小值单元的初值 
dec   cx                             ;循环控制次数4
lp2:
inc   si
inc   si                             ;移动地址指针
mov   ax,[si]                        ;取新数
cmp   ax,max
jle   lp1
mov   max,ax                         ;大于最大换入MAX
jmp   next
lp1:
cmp   ax,min    
jge   next
mov   min,ax                         ;小于最小换入MIN
next: loop  lp2

mov   ah,4ch
int   21h
code  ends
      end   start
