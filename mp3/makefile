# makefile: makefile for assembly-language examples
# 
# Assumes a matched pair of sources, e.g., myprog.s and myprogc.c,
# an assembler source for a function and its C driver.

# Usage: For an assembler source, say myprog.s, with a corresponding 
#  C driver myprogc.c, set A to the basename in the make command line: 
#
#  "make A=myprog myprog.lnx" or just "make A=myprog"
#
#  (since $(A).lnx is the first make target)
#  Then myprog.lnx is ready for downloading via "mtip -f myprog.lnx"
#  (followed by resetting tutor VM and ~d inside the mtip program)

# also "make clean" to clean up non-source files in a directory
# All UNIX tools from ulab had been moved to LINUX by
#
#     Ron Cheung (2/28/2020)
#    
# Fix the mismatching of gcc and gdb debugging header(dwarf=2) problem 
#     3/23/2020
#
# Here the assembler program has the primary source name,
# the C program is just a driver of almost the same basename:
C = $(A)c

# system directories needed for compilers, libraries, header files--
SAPC_TOOLS = /home/cheungr/serl/tutor-linux
PC_LIB = $(SAPC_TOOLS)/libc
PC_INC = $(SAPC_TOOLS)/include


CC    = gcc
CFLAGS  = -gdwarf-2 -gstrict-dwarf -march=i586 -m32 -fno-builtin -fno-stack-protector -nostdlib     -c -Wall -I$(PC_INC)
AS    = as --32
NM    = nm
LD    = ld -m elf_i386

#CC   = $(SAPC_GNUBIN)/i386-gcc
#CFLAGS = -g -Wall -Wno-implicit -Wshadow -I$(PC_INC)
#AS   = $(SAPC_GNUBIN)/i386-as
#LD   = $(SAPC_GNUBIN)/i386-ld
#NM   = $(SAPC_GNUBIN)/i386-nm

# File suffixes:
# .c	C source (often useful both for UNIX host and SAPC)
# .s 	assembly language source
# .o  relocatable machine code, initialized data, etc., for SA PC
# .lnx  executable image (bits as in memory), for SA PC (Linux a.out format)
# .syms text file of .lnx's symbols and their values (the "symbol table")
# Symbol file "syms"--for most recently built executable in directory

# PC executable--tell ld to start code at 0x100100, load special startup
# module, special PC C libraries--

$(A).lnx: $(A).o $(C).o 
	$(LD) -N -Ttext 100100 -o $(A).lnx \
		$(PC_LIB)/startup0.o $(PC_LIB)/startup.o \
		$(C).o $(A).o $(PC_LIB)/libc.a
	rm -f syms;$(NM) -n $(A).lnx>$(A).syms;ln -s $(A).syms syms

$(A).o: $(A).s
	$(AS) -o $(A).o $(A).s

# tell gcc to use $(PC_INC) for #include <...> headers--
$(C).o: $(C).c
	$(CC) $(CFLAGS) -c -o $(C).o $(C).c
	
clean:
	rm -f *.o *.syms *.lnx core syms
