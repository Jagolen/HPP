#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <math.h>
#include <string.h>
#include "testfuncs.h"

static double get_wall_seconds() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  double seconds = tv.tv_sec + (double)tv.tv_usec / 1000000;
  return seconds;
}

int main (int argc, char**args) {

  // Prepare input and output buffers for tests
  const int N1 = 200;
  const int N_extra = 20; // Allocate some extra elements to use for checking that no elements outside N1 are modified.
  const int N1mod = N1 + N_extra;
  double* a1  = (double*)malloc(N1mod*sizeof(double));
  double* a2  = (double*)malloc(N1mod*sizeof(double));
  double* b1  = (double*)malloc(N1mod*sizeof(double));
  double* b2  = (double*)malloc(N1mod*sizeof(double));
  double* c1  = (double*)malloc(N1mod*sizeof(double));
  double* c2  = (double*)malloc(N1mod*sizeof(double));
  int i, j;
  for(i = 0; i < N1mod; i++) {
    a1[i] = (rand() % 1000) * 0.001;
    b1[i] = (rand() % 1000) * 0.001;
    a2[i] = a1[i];
    b2[i] = b1[i];
  }

  memset(c1, 0, N1mod*sizeof(double));
  memset(c2, 0, N1mod*sizeof(double));

  int N2 = 5000000;
  double time1;

  // First run both versions without timings, to get rid of any
  // initialization effects that could disturb the measured timings.
  for(j = 0; j < N2; j++)
    f_std (a1, b1, c1, N1);
  for(j = 0; j < N2; j++)
    f_opt (a2, b2, c2, N1);

  // Test f_std
  time1 = get_wall_seconds();
  for(j = 0; j < N2; j++)
    f_std (a1, b1, c1, N1);
  printf("f_std tests took %7.3f wall seconds.\n", get_wall_seconds()-time1);

  // Test f_opt
  time1 = get_wall_seconds();
  for(j = 0; j < N2; j++)
    f_opt (a2, b2, c2, N1);
  printf("f_opt tests took %7.3f wall seconds.\n", get_wall_seconds()-time1);

  // Check that data after the N1 first elements has not been modified.
  for(i = 0; i < N_extra; i++) {
    if(c1[N1+i] != 0 || c2[N1+i] != 0) {
      printf("\nERROR: modified values outside result buffer.  :-/\n\n");
      return -1;
    }
  }

  // Check that results are the same
  double max_abs_diff = 0;
  for(i = 0; i < N1; i++) {
    double abs_diff = fabs(c2[i] - c1[i]);
    //    printf("data1[i] = %8.4f, abs_diff = %8.4f\n", data1[i], abs_diff);
    if(abs_diff > max_abs_diff)
      max_abs_diff = abs_diff;
  }
  printf("Checking correctness: max_abs_diff = %8.4g\n", max_abs_diff);
  if(max_abs_diff > 1e-12) {
    printf("\nERROR: max_abs_diff too large, result seems wrong.  :-/\n\n");
    return -1;
  }
  printf("OK, result seems correct.\n");

  free(a1);
  free(a2);
  free(b1);
  free(b2);
  free(c1);
  free(c2);

  return 0;
}

