#include <stdio.h>
#include <stdlib.h>

#define FAST 1

#if FAST
int digits2int(int* z, int N)
{
   int zi = 0;
   int *zend = z + N-1;
   do 
   {
      zi = 10*zi + *z;
      z++;
   } while(z <= zend);
   return zi;
}
#else
int digits2int(int* z, int N)
{
   int i;
   int zi = 0;
   for(i = 0; i<N; i++)
   {
      zi = 10 * zi + z[i];
   }
   return zi;
}
#endif

int main(int argc, char** argv)
{
   int numiters = 100000000;
   int i;

   int N = 5;

   int* z = (int*)malloc(N*sizeof(int));
   for(i=0; i<N; i++)
   {
      z[i] = i;
   }  

   int zi;
   for(i=0; i<numiters; i++)
   {
      zi = digits2int(z, N);
   }
   printf("zi = %d\n", zi);

   free(z);

   return 0;
}
