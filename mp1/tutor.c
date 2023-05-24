/******************************************************************
*
*   file:     tutor.c
*   author:   eb
*   date:     September, 1990
*
*   Driver for a "tutor" program to mimic and extend the MECB ROM TUTOR.
* 
*   built from betty o'neil's previous version
*
*   revisions:
*   Jan '96: changed prompt to PC-tutor, now mimics floppy-based Tutor
*/

#include <stdio.h>
#include "slex.h" 
/* The preprocessor symbol SAPC is #defined in $pcinc/stdio.h.  This
 * stdio.h is found by i386-gcc because of the -I flag in its compile command
 * in the Makefile.  In the UNIX case, there is no such redirection,
 * so the ordinary stdio.h is used, and it has no SAPC definition.
 */
#ifdef SAPC
#define PROMPT "PC-tutor> "
#else
#define PROMPT "UNIX-tutor> "
#endif
int main(void);
void getcmd(char *, int *, int *);

int main()
{
  int done = 0;
  int cnum,linepos;
  char linebuf[LINELEN];
  Cmd *cp;

  printf("     cmd    help message\n");
  for(cp = cmds; cp->cmdtoken; cp++) 
      printf("%8s    %s\n", cp->cmdtoken, cp->help);

  while (!done) {
    /* get cmd token from user by parsing first part of line in linebuf-- */
    getcmd(linebuf,&cnum,&linepos);
    /* call implementation routine for matched cmd-- */
    /* (remaining part of line to parse starts at linebuf+linepos) */
    done = cmds[cnum].cmdfn(&cmds[cnum], linebuf+linepos); 
  }
  return 0;
}

/***********************************************************************
*
*  getcmd 
*
* Better than scanf--read whole line in, parse resulting string.
* Uses slex package to match cmd token in first part of linebuf 
* and return command # and where to continue parsing.
* Getcmd loops until user provides proper command, so no error return.
*/
void getcmd(char *linebuf, 
             int *cnum_ptr,   /* returned command number */
             int *pos_ptr     /* position in linebuf (after cmd token) */
           )
{
  int done = 0;

  while (!done) {
     printf( PROMPT );
     gets(linebuf);		/* read line from user, null terminate */
     /* match cmd token to get cnum--call slex package to do lookup-- */
     if (slex( linebuf, cmds, cnum_ptr, pos_ptr)==0) 
         done = 1;	/* success in matching cmd */
     else
         printf(" No such command\n");
  }
}
