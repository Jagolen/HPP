#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
   int i;
   int a = 1, b = 2, c = 3, d = 1;
   float x = 0.1, y = 0.5, z = 0.33;
   const float w = 1/1.33; //used to convert div with 1.33 to multi with w
   printf("%d %d %d %d, %f %f %f\n", a, b, c, d, x, y, z);

   for (i=0; i<50000000; i++)
   {
      c = d+d; //Add faster than multi
      b = c*15;
      a = b>>4; //16 = 2⁴ so bitwise shift 4 to the right
      const int e = b, f = a; //changing to constants instead of variables
      d = e/f; // Faster with constants

      z = 0.33;
      y = z+z; //addition faster
      x = y * w; //multi faster than division
      z = x * w;
   }
   printf("%d %d %d %d, %f %f %f\n", a, b, c, d, x, y, z);
   return 0;
}
