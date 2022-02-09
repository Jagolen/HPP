#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <math.h>
#include "myfunctions.h"

int main (int argc, char**args) {

  const int N1 = 10000;
  double* a  = (double*)malloc(N1*sizeof(double));
  int i, j;
  for(i = 0; i < N1; i++)
    a[i] = (rand() % 1000) * 0.001;

  int N2 = 5000;

  double result = 0;

  for(j = 0; j < N2; j++)
    result = ffff(a, N1);

  printf("result = %f\n", result);
  
  free(a);

  return 0;
}

