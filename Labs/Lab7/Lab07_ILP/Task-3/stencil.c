#include <stdio.h>
#include "stencil.h"

void apply_stencil_v1(const GridPt* grid_src, GridPt* grid_dst, int N) {
  int i, j, k;
  double factor = 1.0 / ( (2*STENCIL_SZ+1) * 2 );
  for(i = STENCIL_SZ; i < N-STENCIL_SZ; i++)
    for(j = STENCIL_SZ; j < N-STENCIL_SZ; j++) {
      double sum = 0;
      for(k = -STENCIL_SZ; k <= STENCIL_SZ; k++)
        sum += grid_src[(i+k)*N+j].x;
      for(k = -STENCIL_SZ; k <= STENCIL_SZ; k++)
        sum += grid_src[i*N+j+k].x;
      grid_dst[i*N+j].x = sum * factor;
    }
}

void apply_stencil_v2(const GridPt* grid_src, GridPt* grid_dst, int N) {
  int i, j, k;
  double factor = 1.0 / ( (2*STENCIL_SZ+1) * 2 );
  for(i = STENCIL_SZ; i < N-STENCIL_SZ; i++)
    for(j = STENCIL_SZ; j < N-STENCIL_SZ; j++) {
      double sum = 0;
      for(k = -STENCIL_SZ; k <= STENCIL_SZ; k++)
        sum += grid_src[(i+k)*N+j].x;
      for(k = -STENCIL_SZ; k <= STENCIL_SZ; k++)
        sum += grid_src[i*N+j+k].x;
      grid_dst[i*N+j].x = sum * factor;
    }
}

void apply_stencil_v3(const GridPt* grid_src, GridPt* grid_dst, int N) {
  const int N_eff = N - 2*STENCIL_SZ;
  const int blockSz = N_eff; // NOTE: CHOOSE BLOCKSIZE HERE! (blockSz = N_eff is like no blocking)
  if(N_eff % blockSz != 0) {
    printf("ERRORin apply_stencil_v3: N_eff not divisible by blockSz.\n");
    return;
  }
  int nBlocks = N_eff / blockSz;
  int start = STENCIL_SZ;
  int stop = N-STENCIL_SZ;
  int i, j, k, blockIdx;
  double factor = 1.0 / ( (2*STENCIL_SZ+1) * 2 );
  for(blockIdx = 0; blockIdx < nBlocks; blockIdx++) {
    int jStart = STENCIL_SZ + blockIdx * blockSz;
    int jStop = jStart + blockSz;
    for(i = start; i < stop; i++) {
      for(j = jStart; j < jStop; j++) {
	double sum = 0;
	for(k = -STENCIL_SZ; k <= STENCIL_SZ; k++)
	  sum += grid_src[(i+k)*N+j].x;
	for(k = -STENCIL_SZ; k <= STENCIL_SZ; k++)
	  sum += grid_src[i*N+j+k].x;
	grid_dst[i*N+j].x = sum * factor;
      }
    }
  }
}

