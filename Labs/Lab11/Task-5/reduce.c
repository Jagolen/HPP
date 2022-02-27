#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

  if(argc != 2) {
    printf("Please give 1 arg: number of threads to use.\n");
    return -1;
  }
  int nThreads = atoi(argv[1]);

  int i;
  const int n = 1000000;
  double sum, globsum;
  double* A;
  A = (double*)malloc(n*sizeof(double));

  for (i = 0; i < n ; i++) { 
    A[i]=(double)i;
  }

  int repeat;
  for(repeat = 0; repeat < 400; repeat++) {

    globsum=0.0;
#pragma omp parallel num_threads(nThreads) private(sum)
    {
      sum=0.0;

#pragma omp for
      for (i = 0; i < n ; i++) { 
	sum += A[i];
      }

#pragma omp critical
      {
	globsum+=sum;
      }
    }

  }

  printf("Global sum is: %f\n",  globsum);

  free(A);

  return 0;
}
