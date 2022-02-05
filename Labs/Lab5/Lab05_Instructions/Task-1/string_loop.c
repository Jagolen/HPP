#include <stdio.h>
#include <stdlib.h>

#define FAST 1

/* From A. Fog Example 7.31. */

#if FAST

void lowercase(char* p)
{
   int i;
   for (i = 100; i>0; i--)
	*(p++) |= 0x20;
   
}

#else

void lowercase(char* p)
{
   while (*p != 0)
	*(p++) |= 0x20;
}

#endif

int main(int argc, char** argv)
{
   int numiters = 10000000;
   char string[100];
   int i;

   
   for(i=0; i<99; i++)
   {
      string[i] = 'A';
   }  
   string[99] = '\0';		/* null-terminate the string */

   for(i=0; i<numiters; i++)
   {
      lowercase(string);
   }
   printf("done\n");

   return 0;
}
