#include "preprocess.h"
#include "preprocess.h"

#define TWO 2

int main()
{
   int two = TWO;
   int sum = add(two, __LINE__);   
}

int add(int a, int b)
{
   return a + b;
}
