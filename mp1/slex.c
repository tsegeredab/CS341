/******************************************************************
*
*   file:   slex.c
*   author: betty o'neil
*   date:   ?
*
*   simple lexical analyzer, front part of a parser                   
*   --compare to UNIX tool "lex", general lexical analyzer            
*   gets a (space-delimited) token from linebuf and tries to match    
*   it to one of the cmdtokens in the provided cmdtable             
*
*   accepts:       
*         linebuf--string to get token from                         
*         cmdtable--cmdtable to use                                 
*   returns:                                                          
*         *cnum_ptr--command # (offset in cmdtable) or -1 if no match
*         *pos_ptr--new place in linebuf after token match          
*
*   improvements needed:
*         make token matching case independent
*         skip whitespace, not just blanks
*
*   revisions: 
*     9/90 cleanup, convert function headers to ansi form
*
*/

#include <stdio.h>
//#include <string.h>
#include "slex.h"		/* for definition of type cmd */
//#include slex.h

int slex(char *linebuf,    /* string from user */
         Cmd cmdtable[],   /* cmd table to use */
         int *cnum_ptr,    /* returned command number */
         int *pos_ptr)      /* returned new place in linebuf */
{
  int i = 0;
  char token[MAXTOKENLEN];
  int newpos;

  if (gettoken(linebuf,token,&newpos)<0) /* get token from linebuf */
    return -1;			/* couldn't find token */

  while ((cmdtable[i].cmdtoken != NULL)) {
    if (strcmp(cmdtable[i].cmdtoken,token)==0) {
	*cnum_ptr = i;		/* success--return command # */
	*pos_ptr = newpos;	/* and where we got to in linebuf */
	return 0;
    }
    else
      i++;			/* keep scanning table */
  }
  return -1;			/* no match */
}

/******************************************************************
 * get one space-delimited token from string in linebuf, also return 
 * new position in string 
 */
int gettoken(char *linebuf, char *token, int *pos_ptr)
{
  int i = 0;
  int j = 0;

  while (linebuf[i] == ' ')
    i++;			/* skip blanks */
  while (linebuf[i] != ' '&&linebuf[i]!='\0')
    token[j++] = linebuf[i++];	/* copy chars to token */
  if (j==0)
    return -1;			/* nothing there */
  else
    {
      token[j] = '\0';		/* null-terminate token */
      *pos_ptr = i;		/* return place in linebuf we got to */
      return 0;			/* success */
    }
}
