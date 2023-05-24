/* timer.c  Test program to see timer running 
 * Build with $pcex/makefile: "make C=timer timer.lnx"  
 *
 * rename the delay function to smalldelay1() to avoid
 * the same function name in timepack_sapc.c if we
 * use the modified makefile --- R. Cheung 4/2015 */

/* the makefile uses gcc -I<dir> to make sure these come from $pcinc-- */
#include <stdio.h>
#include <timer.h>
#include <cpu.h>

#define NTIMES 5
#define MAX 80
void smalldelay1(void);
void showcounts(void);
void setcount(int count);

int main(void)
{
  int count;
  char buf[MAX];

  printf("Enter count for timer (decimal no. <64K): ");
  fgets(buf,MAX,CONSOLE);	/* dev no. CONSOLE def'd in $pcinc/stdio.h */
  sscanf(buf, "%d" ,&count);
  setcount(count);		/* 0 = max, 65536 */
  showcounts();
  showcounts();
  showcounts();
  return 0;
}
/* about 10 usecs on a SAPC (400Mhz Pentium) */
void smalldelay1(void)
{
  int i;
  
  for (i=0;i<1000;i++)
    ;
}

/* Print out timer counts after little delays, to show downcounting.
 * Note we are assuming the calling overhead to outpt and inpt provide 
 * sufficient delay between the accesses to the same port */
void showcounts()
{
  int i, count[NTIMES];

  for (i=0;i<NTIMES;i++) {
    /* command timer 0 to latch count: */
    outpt(TIMER_CNTRL_PORT, TIMER0|TIMER_LATCH);
    count[i] = inpt(TIMER0_COUNT_PORT);	/* read in LSB of count */
    count[i] |= inpt(TIMER0_COUNT_PORT)<<8; /* then MSB of count */
    smalldelay1();
  }
  for (i=0;i<NTIMES;i++) {	/* this takes more time than "delay" */
    printf("%d ",count[i]);
  }
  printf("\n");
}

/* set count to downcount from, in timer: it gets to 0, starts over */
void setcount(int count)
{
  /* set timer 0 count, mode */
  outpt(TIMER_CNTRL_PORT, TIMER0|TIMER_SET_ALL|TIMER_MODE_RATEGEN);
  outpt(TIMER0_COUNT_PORT,count&0xff); /* set LSB here */
  outpt(TIMER0_COUNT_PORT,count>>8); /* and MSB here */
  smalldelay1();			/* let timer have a moment */
}
