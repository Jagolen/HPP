#include <stdlib.h>
#include <stdio.h>

#define FAST 0

int main(int argc, char **argv)
{
  int N = 10000, i, j;
  double sum;
  double * data = (double*) malloc(N*N*sizeof(double));
  for(i = 0; i < N*N; i++)
    data[i] = 0;
   
#if FAST

  printf("fast\n");
  double tmp;
  int iN;
  for(i = 0; i<N; i++) {
    iN = i*N;
    tmp = i*N/7.7;
    for(j = 0; j<N; j++)
      data[iN + j] += tmp + j;
  }

#else

  printf("slow\n");
  for(i = 0; i<N; i++) {
    for(j = 0; j<N; j++)
      data[i*N + j] += i*N/7.7 + j;
  }

#endif

  sum = 0;
  for(i = 0; i < N*N; i++)
    sum += data[i];
  printf("Done. sum = %15.3f\n", sum);

  free(data);

  return 0;
}
