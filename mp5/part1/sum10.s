# sum10.s: S&S, p. 44, add first 10 numbers
# Note that only C scratch regs are used, so we don't have to save and
# restore any regs.

.text
.globl sum10
	
sum10:
	movl	$1, %ecx		# 1 is the first integer to be added
	movl	$0, %eax		# Initialize the sum to zero
addint:	addl 	%ecx,%eax		# Add an int to the sum
	incl	%ecx			# inc the count by 1
	cmpl	$10,%ecx		# compare to decimal 10
	jbe	addint			# jump back if not
	ret

