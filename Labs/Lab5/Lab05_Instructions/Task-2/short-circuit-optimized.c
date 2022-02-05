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
      if(isMostlyTrue() || isMostlyFalse()) //True = Second statement will not be evaluated
         foo += 1;
      
      if(isMostlyFalse() && isMostlyTrue()) //False = Second statement will not be evaluated
         foo += 2;

// Fiftyfifty more likely to be false than mostly true and and fiftyfifty && true is more likely to be true than false && fifty fifty. This setup leads to the least amount of conditions being checked.
      if((isFiftyFifty()&&isMostlyTrue()) || (isMostlyFalse() && isFiftyFifty()))
         foo += 4;                
   }
   printf("foo = %d\n", foo);
   return 0;
}
