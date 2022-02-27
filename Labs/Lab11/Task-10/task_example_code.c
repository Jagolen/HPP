#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* The function f is doing some computations based on its input and
   storing the result in the place pointed to by resultPtr. */
void f(int i, int j, int k, int l, int m, int N, double* resultPtr) {
  double result = 0;
  for(int a = 0; a < j; a++)
    for(int b = 0; b < N*100; b++)
      result += 0.001 * (0.3*a*b + i*b + m*4 + b);
  for(int a = 0; a < k; a++)
    for(int b = 0; b < N*100; b++)
      result += 0.001 * (0.3*a*b + i*b + m*3 + b);
  *resultPtr = result;
}

int main(int argc, char *argv[]) {
  if(argc != 2) {
    printf("Please give 1 arg: N\n");
    return -1;
  }
  int N = atoi(argv[1]);

  printf("N = %d\n", N);

  const int totCount = 2*3*2*3*2;
  printf("totCount = %d\n", totCount);
  double resultVec[totCount];

  int count = 0;
    for(int i = 0; i < 2; i++)
      for(int j = 0; j < 3; j++)
	for(int k = 0; k < 2; k++)
	  for(int l = 0; l < 3; l++)
	    for(int m = 0; m < 2; m++) {
	      f(i, j, k, l, m, N, &resultVec[count]);
	      count++;
	    }

  assert(count == totCount);

  double finalSum = 0;
  for(int i = 0; i < totCount; i++)
    finalSum += resultVec[i];
  printf("finalSum = %f\n", finalSum);
  
  return 0;
}
