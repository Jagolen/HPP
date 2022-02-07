#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <string.h>
#include <math.h>
#include "transpose.h"

static double get_wall_seconds() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  double seconds = tv.tv_sec + (double)tv.tv_usec / 1000000;
  return seconds;
}

int main (int argc, char**args) {
  double time1;
  const int N = 5000;
  const int nJobs = 1;

  double* A     = (double*)malloc(N*N*sizeof(double));
  double* B_std = (double*)malloc(N*N*sizeof(double));
  double* B_opt = (double*)malloc(N*N*sizeof(double));

  // Fill matrix with random numbers
  int i;
  for(i = 0; i < N*N; i++)
    A[i] = rand();

  do_transpose_standard (B_std, A, N);
  do_transpose_optimized(B_opt, A, N);

  // Compare results
  double max_abs_diff = 0;
  for(i = 0; i < N*N; i++) {
    double abs_diff = fabs(B_std[i] - B_opt[i]);
    if(abs_diff > max_abs_diff)
      max_abs_diff = abs_diff;
  }
  printf("Checking correctness: max_abs_diff = %8.4g\n", max_abs_diff);
  if(max_abs_diff > 1e-12) {
    printf("\nERROR: max_abs_diff too large, result seems wrong.  :-/\n\n");
    return -1;
  }
  printf("OK, result seems correct.\n");
    
  time1 = get_wall_seconds();
  for(i = 0; i < nJobs; i++)
    do_transpose_standard(B_std, A, N);
  printf("do_transpose_mod_standard %d times for N=%d took %7.3f wall seconds.\n", nJobs, N, get_wall_seconds()-time1);

  time1 = get_wall_seconds();
  for(i = 0; i < nJobs; i++)
    do_transpose_optimized(B_opt, A, N);
  printf("do_transpose_mod_optimized %d times for N=%d took %7.3f wall seconds.\n", nJobs, N, get_wall_seconds()-time1);

  free(A);
  free(B_std);
  free(B_opt);

  return 0;
}

