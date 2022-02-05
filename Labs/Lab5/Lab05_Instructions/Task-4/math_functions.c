#include <stdio.h>
#include <math.h>

int main(int argc, char **argv)
{
   int i;
   float x;
   for (i=0; i<50000000; i++)
   {
     x = pow(i, 0.5);
     /*
       Alternatives:
       x = sqrt(i);
       x = sqrtf(i);
     */
   }
   printf("%f\n", x);
   return 0;
}
