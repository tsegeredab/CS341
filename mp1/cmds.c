/******************************************************************
*
*   file:     cmds.c
*   author:   betty o'neil
*   date:     ?
*
*   semantic actions for commands called by tutor (cs341, mp1)
*
*   revisions:
*      9/90  eb   cleanup, convert function declarations to ansi
*      9/91  eb   changes so that this can be used for hw1
*      9/02  re   minor changes to quit command
*/
/* the Makefile arranges that #include <..> searches in the right
   places for these headers-- 200920*/

#include <stdio.h>
#include "slex.h"
/*===================================================================*
*
*   Command table for tutor program -- an array of structures of type
*   cmd -- for each command provide the token, the function to call when
*   that token is found, and the help message.
*
*   slex.h contains the typdef for struct cmd, and declares the
*   cmds array as extern to all the other parts of the program.
*   Code in slex.c parses user input command line and calls the
*   requested semantic action, passing a pointer to the cmd struct
*   and any arguments the user may have entered.
*
*===================================================================*/

PROTOTYPE int stop(Cmd *cp, char *arguments);
PROTOTYPE int mem_display(Cmd *cp, char *arguments);
PROTOTYPE int mem_set(Cmd *cp, char *arguments);
PROTOTYPE int help(Cmd *cp, char *arguments);
PROTOTYPE unsigned int atox(char **arguments);

/* command table */

Cmd cmds[] = {{"md",  mem_display, "Memory display: MD <addr>"},
              {"s",   stop,        "Stop" },
              {"h", help,	   "Help:<cmd>"},
	      {"ms", mem_set,	  "Memory set: MS <Hexaddress> <new_value>"},
              {NULL,  NULL,        NULL}};  /* null cmd to flag end of table */

char xyz = 6;  /* test global variable  */
char *pxyz = &xyz;  /* test pointer to xyz */
/*===================================================================*
*		command			routines
*
*   Each command routine is called with 2 args, the remaining
*   part of the line to parse and a pointer to the struct cmd for this
*   command. Each returns 0 for continue or 1 for all-done.
*
*===================================================================*/

int stop(Cmd *cp, char *arguments)
{
  return 1;			/* all done flag */
}

/*===================================================================*
*
*   mem_display: display contents of 16 bytes in hex
*
*/

int mem_display(Cmd *cp, char *arguments)
{
	int i;
int address = 0;
unsigned char *padrs;
sscanf(arguments, "%x", &address);
padrs = (char *)address;

printf("Tsegereda: %x; %02x ", address, *padrs++);  

  for(i=0;i <16; i++)
	printf("%02x ", *padrs++); 
   padrs = (unsigned char *)address;
   printf("\n");
   for(i=0;i<16;i++)
	if(*padrs > 0x20 && *padrs < 0x7F)
		printf("%c", *padrs++);
	else
	{	
		printf(".");
		padrs++;
	}

   printf("\n");
  printf("Reached mem_display, passed argument string: |%s|\n", arguments);
  printf("        help message: %s\n", cp->help);
  return 0;			/* not done */
}
/* mem_set
*/
int mem_set(Cmd *cp, char *arguments) {
	int address = 0;
	int value = 0;
	char *padrs;
	sscanf(arguments,"%x %x", &address, &value);
	padrs = (char *)address;
	*padrs = value;
		 
	return 0;	

}
/* help
*/
int help(Cmd *cp, char *arguments) {
char string[2];
	int num = 0;
	int length = sizeof(cmds)/sizeof(Cmd);
	sscanf(arguments, "%s", string);
	for(num=0; num < length-1;num++)
		if((strcmp(cmds[num].cmdtoken, string)) == 0)
			printf("%s\n", cmds[num].help);

	return 0;
}
