   # function to restart the application
.globl reboot
   .text
reboot:
   jmp 0x100100                    #rreboot code
   ret              
   .end

