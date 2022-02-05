#include <stdio.h>
#include <string.h>

/*
Find all permutations of a string.

Code: http://www.geeksforgeeks.org/write-a-c-program-to-print-all-permutations-of-a-given-string/
*/

unsigned long count = 0; // count permutations

/* Swap values pointed by x and y */
void swap(char *x, char *y)
{
   char tmp;

   tmp = *x;
   *x  = *y;
   *y  = tmp;
}


/* Function to print permutations of string
 * This function takes three parameters:
 * 1. String
 * 2. Starting index of the string
 * 3. Ending index of the string. */
void permute(char *a, int l, int r)
{
   if (l == r)
   {
      //printf("%s\n", a);
      count++;
      return;
   }

   for (int i = l; i <= r; i++)
   {
      swap((a + l), (a + i));
      permute(a, l + 1, r);
      swap((a + l), (a + i)); //backtrack
   }
}


int main(int argc, char const *argv[])
{
   if (argc != 2)
   {
      printf("Usage: %s string\n", argv[0]);
      return -1;
   }
   char str[100];
   strcpy(str, argv[1]);
   printf("Permutations of %s are:\n", str);
   int n = strlen(str);
   permute(str, 0, n - 1);
   printf("In total %ld permutations\n", count);
   return 0;
}
