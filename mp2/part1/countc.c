/* countc.c: call assembly soubroutine to count c's in string 
    bob wilson
      4/28/2016
     modifed by Ron Cheung
      3/2/2020
 */

#include <stdio.h>
extern int count(char *string, char c);

int main(void)
{
  char s[100];
  char c;
  printf("Enter a string of characters:\n");
  scanf("%s", s);
  printf("Enter a character to count:\n");
  scanf("%c", &c);
  printf("\nThe number of %c's in the string %s is %d\n", c, s, count(s, 
c));
  return 0;
}
