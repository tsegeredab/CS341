/* sum10c.c: driver for sum10.s: print out return value from sum10 code */
#include <stdio.h>
extern int sum10(void);
int main()
{
  printf("sum of 10 ints is %d\n",sum10());
}
