#include <stdlib.h>
#include <stdio.h>
#include <string.h> /* contains memset and memcpy, oddly enough. */

/* From A. Fog: Example 7.33. */

#define FAST 0

int main(int argc, char** argv)
{
   const int size = 1000;  int i, j;
   float a[size], b[size];
   for(j=0; j<100000; j++)
   {
#if FAST
     /* set a to zero. */
      memset(a, 0, sizeof(a));
      /* copy a to b. */
      /* memcpy(b, a, sizeof(b)); */  /* memcpy okay to use for non-overlapping arrays. */
      memmove(b, a, sizeof(b));	/* memmove always okay to use. */
#else
      /* set a to zero. */
      for (i = 0; i < size; i++) 
         a[i] = 0.0;
      /* copy a to b. */
      for (i = 0; i < size; i++) 
         b[i] = a[i];
#endif
   }
   /* Check that a and b have same contents. */
   int diffFound = 0;
   for (i = 0; i < size; i++) {
     if(b[i] != a[i])
       diffFound = 1;
   }
   printf("diffFound = %d\n", diffFound);
   return 0;
}
