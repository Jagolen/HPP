#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <math.h>
#include "testfuncs.h"

static double get_wall_seconds() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  double seconds = tv.tv_sec + (double)tv.tv_usec / 1000000;
  return seconds;
}

int main (int argc, char**args) {

  // Prepare input and output buffers for tests
  const int N1 = 10000;
  double* a  = (double*)malloc(N1*sizeof(double));
  int i, j;
  for(i = 0; i < N1; i++)
    a[i] = (rand() % 1000) * 0.001;

  int N2 = 20000;
  double time1;

  double result_std = 0;
  double result_opt = 0;

  // First run both versions without timings, to get rid of any
  // initialization effects that could disturb the measured timings.
  for(j = 0; j < N2; j++)
    result_std = f_std (a, N1);
  for(j = 0; j < N2; j++)
    result_opt = f_opt (a, N1);

  // Test f_std
  time1 = get_wall_seconds();
  for(j = 0; j < N2; j++)
    result_std = f_std (a, N1);
  printf("f_std tests took %7.3f wall seconds.\n", get_wall_seconds()-time1);

  // Test f_opt
  time1 = get_wall_seconds();
  for(j = 0; j < N2; j++)
    result_opt = f_opt (a, N1);
  printf("f_opt tests took %7.3f wall seconds.\n", get_wall_seconds()-time1);
  
  // Check that results are the same
  double abs_diff = fabs(result_opt - result_std);
  printf("Checking correctness: abs_diff = %8.4g\n", abs_diff);
  if(abs_diff > 1e-12) {
    printf("\nERROR: abs_diff too large, result seems wrong.  :-/\n\n");
    return -1;
  }
  printf("OK, result seems correct.\n");

  free(a);

  return 0;
}

