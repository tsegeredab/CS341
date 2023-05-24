/* echo.c: use assembly language i/o to echo console input */
/* build with makefile in mp2:  make A=echo      */

#include <stdio.h>
#include <serial.h>

extern void echo(int conport, unsigned char esc_char);
int main()
{
  int console = sys_get_console_dev(); /* find out current sys console */
  int conport;
  char escape;

  switch (console) {
  case COM1: conport = COM1_BASE;
    break;
  case COM2: conport = COM2_BASE;
    break;
  default: printf("Expected serial port for console, exiting\n");
    return 0;
  }

  printf("Type escape character and enter\n");
  if (scanf("%c\n", &escape) != 1)
    escape = 0x01;
  echo(conport, escape);
  return 0;
}
