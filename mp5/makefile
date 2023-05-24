# makefile: makefile for building watchdog.lnx
# 
#    make watchdog.lnx
#
# also "make clean" to clean up non-source files in a directory
# All UNIX tools from ulab had been moved to LINUX by
#
#     Ron Cheung (2/28/2020)
#    
# Fix the mismatching of gcc and gdb debugging header(dwarf=2) problem 
#     3/23/2020
#
#
# system directories needed for compilers, libraries, header files--
SAPC_TOOLS = /home/cheungr/serl/tutor-linux
PC_LIB = $(SAPC_TOOLS)/libc
PC_INC = $(SAPC_TOOLS)/include


CC    = gcc
CFLAGS  = -gdwarf-2 -gstrict-dwarf -march=i586 -m32 -fno-builtin -fno-stack-protector -nostdlib     -c -Wall -I$(PC_INC)
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

# PC executable--tell ld to start code at 0x100100, load special startup
# module, special PC C libraries--

watchdog.lnx: reboot.o watchdog.o timepack_sapc.o
	$(LD) -N -Ttext 100100 -o watchdog.lnx \
		$(PC_LIB)/startup0.o $(PC_LIB)/startup.o \
		watchdog.o reboot.o timepack_sapc.o $(PC_LIB)/libc.a
	rm -f syms;$(NM) -n watchdog.lnx>watchdog.syms;ln -s watchdog.syms syms

reboot.o: reboot.s
	$(AS) -o reboot.o reboot.s

watchdog.o: watchdog.c
	$(CC) $(CFLAGS) -c -o watchdog.o watchdog.c
	
timepack_sapc.o: timepack_sapc.c timepack.h
	$(CC) $(CFLAGS) -c -o timepack_sapc.o timepack_sapc.c

clean:
	rm -f *.o *.syms *.lnx core syms
