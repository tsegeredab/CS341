/* strncpyc.c: driver for testing assembly language mystrncpy function 
	Bob Wilson
	4/28/2016
     Modified by Ron Cheung 3/4/2019
   */

#include <stdio.h>
extern char *mystrncpy(char *s, char *ct, int n);

int main()
{
   char s[10], ct[100];
   int n;

  printf("Enter a string of characters:\n");
  /* read all inputs until the \n character */
  scanf("%[^\n]s", ct);
  printf("Enter the number of characters to copy:\n");
  scanf("%d", &n);

  if(s == mystrncpy(s, ct,n))
      printf("The strncpy function returned the correct pointer value.\n");
  else
      printf("The strncpy function returned the wrong pointer value.\n");
  if (!strncmp(s,ct, n))
      printf("The strncpy function copied the data correctly.\n");
  else
      printf("The strncpy function copied the data incorrectly.\n");
  printf("The content of the first %d characters of array s is: %s\n",n, s);
  return 0;	
}
