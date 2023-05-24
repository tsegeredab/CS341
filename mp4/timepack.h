/******************************************************************
*
*   file:      timepack.h
*   author:    Ethan Bolker
*   date:      October 1990
*
*   revisions: Betty O'Neil, March 1992, 1996 to PC
*              Richard Eckhouse, March 1993
*
*   Header file for timing package for CS241
*
*   #include this file in the source code for the package
*   (that file will usually be named "timepack_xxxx.c",
*   where xxxx is the targeted machine, e.g. unix or sapc)
*   and in any source code that calls the routines in the package.
*/

/***************************************************************
*  return codes
*/
#define T_OK          0	      /* 0 is the standard success return */
/* negative return vals are used for various kinds of failures-- */
#define T_RUNNING    -2       /* clock running */
#define T_STOPPED    -3       /* clock not running */
#define T_DONT_KNOW  -4       /* possible value for clock precision */

#ifndef PROTOTYPE
#define PROTOTYPE
#endif

/***************************************************************
*
* initialize the timer and/or the software package as necessary.
*/
PROTOTYPE void inittimer(void);

/***************************************************************
*
* undo any initialization of the timer and/or the software package.
*/
PROTOTYPE void shutdowntimer(void);

/***************************************************************
*
*  query the timing package to determine the precision, in integer
*  # of microseconds, and if timer running (Boolean 0/1 val).
*
*  returns values in the variables *running and *precision
*
*  note that T_DONT_KNOW may be returned for precision,
*  useful for stubs, and for timesharing systems.
*/
PROTOTYPE void querytimer(int *precision, int *running);

/***************************************************************
*
*   if clock is not running
*      start the timer
*      return T_OK
*   else return T_RUNNING
*/
PROTOTYPE int starttimer(void);

/***************************************************************
*
*      if clock is not running return T_STOPPED
*      stop the timer
*      else
*         set *elapsed = the number of integer number of microsec
*            since starttimer called
*         return T_OK
*/
PROTOTYPE int stoptimer( int *elapsed );


