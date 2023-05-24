/* typewr.c: echo on COM2 using UART receiver interrupts                 */
/* The needed interrupt envelope routines irq3int, etc. are in           */
/*   the library, and sti, cli, pic_enable_irq, etc., are there too.     */
#include <stdio.h>
#include <serial.h>
#include <cpu.h>
#include <pic.h>
#include "timepack.h"

extern IntHandler irq3inthand; /* the assembler envelope routine    */
void irq3inthandc(void);  /* the C core int handler, called from envelope */

int done;			/* global for communication with int hand */
int time;

/* Note in our enviroment, interrupts are normally enabled in the CPU, so we
   use cli() as necessary even at the very start of the program */
int main(void)
{
  if (sys_get_console_dev() != COM2)
    printf("Warning: console not COM2, so echos won't show on console\n");

  /* init global explicitly, so program works properly on reruns */
  done = 0;			
				 
  cli();			/* disable ints while setting them up */
  printf("Calling set_intr_gate (irq = 3, n = 0x23) to arm interrupt...\n");
  set_intr_gate(COM2_IRQ+IRQ_TO_INT_N_SHIFT, &irq3inthand);

  printf("Commanding PIC to interrupt CPU for irq 3 (COM2_IRQ)\n");
  pic_enable_irq(COM2_IRQ);

  printf("enabling receiver interrupts in UART...\n");
  outpt(COM2_BASE+UART_IER, UART_IER_RDI); /* RDI = receiver data int */
  /*  now hardware reg's are all set up, time to allow CPU ints-- */
 inittimer();
  sti();
  printf("...done, entering almost-infinite loop\n");
  starttimer();

  while (!done)			/* loop almost forever...*/
    ;
  /* here when user types 'q': shutdown ints we started up */
  cli();
  pic_disable_irq(COM2_IRQ);	/* done with irq 3 in PIC */
  outpt(COM2_BASE+UART_IER, 0); /* stop UART ints */
  sti();			/* but other ints still there */
  return 0;
}

/* this is called from irq3inthand, the assembler interrupt envelope routine */
/* that saves the C scratch regs on the stack, restores them after this,  */
/* then does the iret instruction.                                        */
void irq3inthandc(void)
{
  char ch;

  stoptimer(&time);
  starttimer();
  pic_end_int();		/* notify PIC that its part is done */
  ch = inpt(COM2_BASE+UART_RX);	/* read char (ACKs UART too) */
  printf("time interval= %d us for char=", time);
  if (ch == 'z')
    done = 1;			/* set global flag to let main know */
  outpt(COM2_BASE+UART_TX,ch); /* echo char (Transmitter should be ready) */
  outpt(COM2_BASE+UART_TX,0xd); /*output a CR */
  outpt(COM2_BASE+UART_TX,0xa);/* output a LF */
}
