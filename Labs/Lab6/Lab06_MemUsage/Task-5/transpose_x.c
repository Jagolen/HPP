#include <stdio.h>
#include "transpose.h"

void do_transpose_x_standard (double** B, int nB, const double* A, int N) {
  int i, j, k;
  for(i = 0; i < N; i++)
    for(j = 0; j < N; j++)
      for(k = 0; k < nB; k++)
	B[k][j*N+i] = A[i*N+j];
}

void do_transpose_x_optimized(double** B, int nB, const double* A, int N) {
  const int blockSz = 100;
  double subMat[blockSz*blockSz];
  if(N % blockSz != 0) {
    printf("Error: N not divisible by blockSz.\n");
    return;
  }
  int nBlocks = N / blockSz;
  int i, j, k, block_i, block_j;
  for(block_i = 0; block_i < nBlocks; block_i++) {
    int iStart = block_i*blockSz;
    for(block_j = 0; block_j < nBlocks; block_j++) {
      int jStart = block_j*blockSz;
      // Copy current block to subMat
      for(i = 0; i < blockSz; i++)
	for(j = 0; j < blockSz; j++)
	  subMat[j*blockSz+i] = A[(iStart+i)*N+(jStart+j)];
      // Copy transposed block to B
      for(i = 0; i < blockSz; i++)
	for(j = 0; j < blockSz; j++)
	  for(k = 0; k < nB; k++)
	    B[k][(jStart+i)*N+(iStart+j)] = subMat[i*blockSz+j];
    }
  }
}

