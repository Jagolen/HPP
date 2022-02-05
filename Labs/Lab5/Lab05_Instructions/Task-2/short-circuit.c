#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int isMostlyTrue()
{
   int r90 = ((float)rand()/RAND_MAX < 0.90)?1:0;
   return r90;
}

int isMostlyFalse()
{
   int r10 = ((float)rand()/RAND_MAX < 0.10)?1:0;
   return r10;
}

int isFiftyFifty()
{
   int r50 = ((float)rand()/RAND_MAX < 0.50)?1:0;
   return r50;
}

int main(int argc, char **argv)
{
   int i, foo;
   srand (time(NULL));
   for (i=0; i<2000000; i++)
   {
      foo = 0;
      /* improve the following if-statements with boolean short-circuits. */
      if(isMostlyFalse() || isMostlyTrue())
         foo += 1;
      
      if(isMostlyTrue() && isMostlyFalse())
         foo += 2;

      if( (isFiftyFifty()&&isMostlyFalse()) || (isFiftyFifty()&&isMostlyTrue()) )
         foo += 4;                
   }
   printf("foo = %d\n", foo);
   return 0;
}
