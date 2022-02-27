#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

typedef float floatType;

void computePart(floatType* A, floatType* B, floatType* C, int N, int M, int iStart, int iCount) {
  int i, j;
  for(j = 0; j < M; j++)
    for(i = iStart; i < iStart+iCount; i++)
      C[i] += A[j*N+i] + B[j];
}

void compute(floatType* A, floatType* B, floatType* C, int N, int M, int nThreads) {
  int k;
  if(N % 2 != 0) {
    printf("ERROR: N must be divisible by 2\n");
    exit(EXIT_FAILURE);
  }
  int partSize = 2;
  int nParts = N / partSize;
  if(nParts < nThreads) {
    printf("ERROR: (nParts < nThreads). This is not going to work.\n");
    exit(1);
  }
#pragma omp parallel for num_threads(nThreads)
  for(k = 0; k < nParts; k++)
    computePart(A, B, C, N, M, k*partSize, partSize);
}

int main(int argc, char *argv[]) {

  if(argc != 4) {
    printf("Please give 3 args: N M nThreads\n");
    return -1;
  }
  int N = atoi(argv[1]);
  int M = atoi(argv[2]);
  int nThreads = atoi(argv[3]);

  printf("N = %d\n", N);
  printf("M = %d\n", M);
  printf("nThreads = %d\n", nThreads);

  /* Setup input arrays A and B initialized with some random
     numbers. */
  int nBytesA = N*M*sizeof(floatType);
  printf("nBytesA = %d\n", nBytesA);
  floatType* A = (floatType*)malloc(nBytesA);
  floatType* B = (floatType*)malloc(M*sizeof(floatType));  
  floatType* C = (floatType*)malloc(N*sizeof(floatType));  
  int i, j;
  for(i = 0; i < M; i++)
    for(j = 0; j < N; j++)
      A[i*N+j] = (rand() % 1000) * 0.002;
  for(i = 0; i < M; i++)
    B[i] = (rand() % 1000) * 0.002;
  /* Initialize C to zero. */
  for(i = 0; i < N; i++)
    C[i] = 0;

  int repeat = 0;
  for(repeat = 0; repeat < 200; repeat++) {
    compute(A, B, C, N, M, nThreads);
  }

  floatType finalSum = 0;
  for(i = 0; i < N; i++)
    finalSum += C[i];
  printf("finalSum = %f\n", finalSum);
  
  return 0;
}
