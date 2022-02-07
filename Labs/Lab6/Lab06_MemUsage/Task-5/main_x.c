#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <string.h>
#include <math.h>
#include "transpose_x.h"

static double get_wall_seconds() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  double seconds = tv.tv_sec + (double)tv.tv_usec / 1000000;
  return seconds;
}

int main (int argc, char**args) {
  double time1;
  const int N = 3000;
  const int nJobs = 1;

  double* A     = (double*)malloc(N*N*sizeof(double));
  const int nB = 5;
  double* B_std[nB];
  double* B_opt[nB];
  int i, j;
  for(i = 0; i < nB; i++) {
    B_std[i] = (double*)malloc(N*N*sizeof(double));
    B_opt[i] = (double*)malloc(N*N*sizeof(double));
  }
  // Fill matrix A with random numbers
  for(i = 0; i < N*N; i++)
    A[i] = rand();

  do_transpose_x_standard (B_std, nB, A, N);
  do_transpose_x_optimized(B_opt, nB, A, N);

  // Compare results
  double max_abs_diff = 0;
  for(j = 0; j < nB; j++) {
    for(i = 0; i < N*N; i++) {
      double abs_diff = fabs(B_std[j][i] - B_opt[j][i]);
      if(abs_diff > max_abs_diff)
	max_abs_diff = abs_diff;
    }
  }
  printf("Checking correctness: max_abs_diff = %8.4g\n", max_abs_diff);
  if(max_abs_diff > 1e-12) {
    printf("\nERROR: max_abs_diff too large, result seems wrong.  :-/\n\n");
    return -1;
  }
  printf("OK, result seems correct.\n");
    
  time1 = get_wall_seconds();
  for(i = 0; i < nJobs; i++)
    do_transpose_x_standard(B_std, nB, A, N);
  printf("do_transpose_mod_standard %d times for N=%d took %7.3f wall seconds.\n", nJobs, N, get_wall_seconds()-time1);

  time1 = get_wall_seconds();
  for(i = 0; i < nJobs; i++)
    do_transpose_x_optimized(B_opt, nB, A, N);
  printf("do_transpose_mod_optimized %d times for N=%d took %7.3f wall seconds.\n", nJobs, N, get_wall_seconds()-time1);

  free(A);
  for(i = 0; i < nB; i++) {
    free(B_std[i]);
    free(B_opt[i]);
  }

  return 0;
}

