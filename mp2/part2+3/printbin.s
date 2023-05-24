.text
.global printbin
.data
string:
   .ascii "xxxx xxxx\0"

printbin:
    pushl %ebp       #enter (setup stack frame)
    movl %esp, %ebp

   # subl $4, %esp
    movb 8(%ebp), %al       # put value to display in al
    movl $string, %edx	    #Set up pointer to string
    call doinibble          # conv.to  4 ASCII  bits and add
    movb $ ' ', (%edx)      #add a space to the string
    incl %edx			# and increment pointer
    call doinibble		#
    movl $string, %eax		# set up return in eax
    movl %ebp, %esp		# remove stack frame (leave)
    popl %ebp
    ret
doinibble:
    movl $4, %ecx		#loop 4 times
loop0:
    shlb $1, %al       #hift msb  bit to carry flag
    jc loop1
    movb $'0', (%edx)
    jmp loop2
loop1:
    movb $'1',(%edx)     #add ascii 1 to string
 loop2:
    incl %edx       #increment pointer to string
    loop loop0      # decrement,tes, and branch back or
    ret             # return to caller

