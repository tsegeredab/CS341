/* watchdog.c - program to simulate a watchdog timer
   using code from typewr.c
   The needed interrupt envelope routines irq3int, etc. are in           
   the library, and sti, cli, pic_enable_irq, etc., are there too.     */
#include <stdio.h>
#include <serial.h>
#include <cpu.h>
#include <pic.h>
#include "timepack.h"
//#include <sys/cdefs.h>
extern IntHandler irq3inthand; /* the assembler envelope routine    */
void irq3inthandc(void);  /* the C core int handler, called from envelope */
void do_work(void);
void shutdown(void);
void kick_dog(void);

int done = 0;			/* global for communication with int hand */
int count = 0;
char ch;
char save_ch = '\0';

/* Note in our enviroment, interrupts are normally enabled in the CPU, so we
   use cli() as necessary even at the very start of the program */
int main(void)
{

  /* init global explicitly, so program works properly on reruns */
  done = 0;			
				 
  cli();			/* disable ints while setting them up */

  // set up interrupt for COM2 port
  printf("Calling set_intr_gate (irq = 3, n = 0x23) to arm interrupt...\n");
  set_intr_gate(COM2_IRQ+IRQ_TO_INT_N_SHIFT, &irq3inthand);

  printf("Commanding PIC to interrupt CPU for irq 3 (COM2_IRQ)\n");
  pic_enable_irq(COM2_IRQ);

  printf("enabling receiver interrupts in UART...\n");
  outpt(COM2_BASE+UART_IER, UART_IER_RDI); /* RDI = receiver data int */
 //
 // insert code to set up timer interrupt
//inittimer();  
  sti();
 //
 // enter into the main function
   printf("...done, entering almost-infinite loop\n");

   while (!done)			/* loop almost forever...*/
   {
     do_work();                         /* loop to do work */
     kick_dog(); 
  }

  //
  // All done
    shutdown();
  return 0;
}


// Function to take character received and display them with comments
void do_work(void)
{
   if(save_ch != ch)
   { 
        printf("new char received is= %c\n", ch);
        save_ch = ch;
   }
   //simulate software failure
   while (count >9 );  /* infinite loop when receiver char count >=10 */
}
void kick_dog(void){
set_timer_count(0);
inittimer();
}
void shutdown(void){
  /* here when user types 'q': shutdown ints we started up */
  cli();
  pic_disable_irq(COM2_IRQ);	/* done with irq 3 in PIC */
  outpt(COM2_BASE+UART_IER, 0); /* stop UART ints */
  sti();			/* but other ints still there */
}

/* this is called from irq3inthand, the assembler interrupt envelope routine */
/* that saves the C scratch regs on the stack, restores them after this,  */
/* then does the iret instruction.                                        */
void irq3inthandc(void)
{
  count++;
  pic_end_int();		/* notify PIC that its part is done */
  ch = inpt(COM2_BASE+UART_RX);	/* read char (ACKs UART too) */
  if (ch == 'z')
    done = 1;			/* set global flag to let main know */
}
