/******************************************************************
*
*   file:     slex.h
*   author:   eb
*   date:     September, 1990
*
*   header file for lexical analyzer slex.h
*   built from betty o'neil's previous version
*   revisions:
*
*/
#ifndef PROTOTYPE
#define PROTOTYPE    /* label ANSI C function prototypes with empty string */
#endif

#define LINELEN 80
#define MAXTOKENLEN 80

/****************************************************************************
 *  What is a command? This typedef takes an object oriented view
 *  of the answer to that question.
 */
typedef struct cmdtag {
  char *cmdtoken;		/* md or whatever--char string to invoke cmd */
  int (*cmdfn)(struct cmdtag *, char *);  /* function to call for this cmd */
  char *help;			/* helpstring for cmd */
} Cmd;

/****************************************************************************
 *  Tell the world that someone will provide space for and contents of
 *  the command table. 
 */

extern Cmd cmds[];


/****************************************************************************
 *  A function prototype for the lexical analyzer:
 */

PROTOTYPE int slex(char *linebuf,    /* string from user */
                   Cmd cmdtable[],   /* cmd table to use */
                   int *cnum_ptr,    /* returned command number */
                   int *pos_ptr      /* returned new place in linebuf */
                  ) ;

/****************************************************************************
 *  A function prototype for gettoken, called by lexical analyzer
 */

PROTOTYPE int gettoken(char *linebuf, char *token, int *pos_ptr);

/****************************************************************************
 *  A function prototype for getcmd, called by tutor main line
 */

PROTOTYPE void getcmd(char *linebuf, int *cnum_ptr, int *pos_ptr);

