.text
	.global mystrncpy
mystrncpy:
    pushl %ebp         #creating a stack fram
    movl %esp, %ebp    #set esp to ebp register

    movl 8(%ebp), %ecx     	#get argument s
    movl 12(%ebp), %edx		#get argument ct
    movl 16(%ebp), %edi		#get argument n    
    
loop:			                #string copy operation
    movb (%edx), %al
    movb %al, (%ecx)		#via al to destination
    incl %ecx			# increment to pointer
    incl %edx			# increment from pointer
    decl %edi			# decrement bumber of bytes moved n
    cmpb $0, %al		#check for null terminator
    jz exit
    cmpl $0, %edi
    jnz loop
exit:
    movl 8(%ebp), %eax      #then return the address of  s in %eax8
    movl %ebp, %esp		#remove stack frame
    popl %ebp
    ret
    .end
