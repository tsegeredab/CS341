# tiny.s: mp2warmup program

        .globl _start
_start:
	movl $8, %eax
	addl $0x3, %eax
	movl %eax, 0x200
	int $3
   	.end

