#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
   int i;
   float tiny = 1e-39;

   printf("%e\n", tiny);

   /* Inside the loop we do some computations modifying the "tiny"
      variable in such a way that it is (almost) restored to the same
      value again in each loop iteration. The value will probably
      change slightly due to rounding errors. */
   for (i=0; i<5000000; i++)
   {
      tiny += tiny/2.0;
      tiny *= 0.666667;
      tiny += tiny/2.0;
      tiny *= 0.666667;
      tiny += tiny/2.0;
      tiny *= 0.666666;
   }
   printf("%e\n", tiny);

   return 0;
}
