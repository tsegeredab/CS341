# makefile for mp4's measure program 
# makefile with one additional include dir, and timepack_sapc.c
# Usage: 
#    make C=measure   
#
# makefile for building C or assembly language programs for the
# Standalone 486 or Pentium IBM PC running in 32-bit protected mode, 
# Single-source-file makefile--needs editing for multiple-module programs

# For a C source, say myprog.c, override the "C=ctest" below by
#  setting C in the make command line: "make C=myprog myprog.lnx"
#  or just "make C=myprog", since $(C).lnx is the first make target.
#  Then myprog.lnx is ready for downloading via "mtip -f myprog.lnx"
#  (followed by ~d inside the mtip program)
C = ctest

# also "make clean" to clean up non-source files in a directory
# All UNIX tools from ulab had been moved to LINUX by
#
#     Ron Cheung (2/28/2020)
#
# Fix the mismatching of gcc and gdb debugging header(dwarf=2) problem
#     3/23/2020
#
# system directories needed for compilers, libraries, header files--
SAPC_TOOLS = /home/cheungr/serl/tutor-linux
PC_LIB = $(SAPC_TOOLS)/libc
PC_INC = $(SAPC_TOOLS)/include

CC    = gcc
CFLAGS  = -gdwarf-2 -gstrict-dwarf -march=i586 -m32 -fno-builtin -fno-stack-protector -nostdlib -c -Wall -I$(PC_INC)
AS    = as --32
NM    = nm
LD    = ld -m elf_i386

# File suffixes:
# .c	C source (often useful both for UNIX host and SAPC)
# .s 	assembly language source
# .o  relocatable machine code, initialized data, etc., for SA PC
# .lnx  executable image (bits as in memory), for SA PC (Linux a.out format)
# .syms text file of .lnx's symbols and their values (the "symbol table")
# Symbol file "syms"--for most recently built executable in directory

# PC executable--tell ld to start code at 0x1000e0, load special startup
# module, special PC C libraries--
# This executable also contains  timepack_sapc.o
$(C).lnx: $(C).o timepack_sapc.o $(PC_LIB)/libc.a \
			$(PC_LIB)/startup.o $(PC_LIB)/startup0.o
	$(LD) -N -Ttext 100100 -o $(C).lnx \
		$(PC_LIB)/startup0.o $(PC_LIB)/startup.o \
		$(C).o timepack_sapc.o $(PC_LIB)/libc.a
	rm -f syms;$(NM) -n $(C).lnx>$(C).syms;ln -s $(C).syms syms

# tell gcc to use $(PC_INC) for #include <...> headers--
$(C).o: $(C).c
	$(CC) $(CFLAGS) -c -o $(C).o $(C).c

timepack_sapc.o: timepack_sapc.c timepack.h
	$(CC) $(CFLAGS) -c -o timepack_sapc.o timepack_sapc.c

clean:
	rm -f *.o *.syms *.lnx core syms
