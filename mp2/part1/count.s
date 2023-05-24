.text
 .globl count
 
count:
 pushl %ebp        #Creating a stack
        movl  %esp, %ebp  # Setting the esp value to ebp
        subl $8, %esp   # Substracting 8 decimal from the address of the register %esp
        movl 12(%ebp), %edx  # char set 
        movl 8(%ebp), %ecx   # string set
 movl $0, %eax        # counter set 0
        
loop: 
       cmpb %dl, (%ecx)     # compare the single character with each character in the string
       jz  sum             #jumping to the sum
       cmpb $0x00, (%ecx)   # compare the character 
       jz  end                
       addl $1, %ecx         # going to next character
       jmp loop               #jumping to loop
                     
sum:                             #this part to sum up the number of characters
      addl $1, %eax          # increment counter sum
      addl $1, %ecx          
      jmp loop

end: 
      movl %ebp, %esp        # back to main
      popl %ebp
      ret
