#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "myfuncs.h"

int main(int argc, char* argv[]) {
  const int N = 88;
  float* v = (float*)malloc(N*sizeof(float));
  int k;
  for(k = 0; k < N; k++)
    v[k] = 0.3*k;
  float f1, f2;
  f1 = fun1(v, N);
  f2 = fun2(v, N);
  printf("f1 = %f, f2 = %f\n", f1, f2);
  free(v);
  return 0;
}
