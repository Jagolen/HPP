#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <math.h>
#include "testfunc1.h"
#include "testfunc2.h"

static double get_wall_seconds() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  double seconds = tv.tv_sec + (double)tv.tv_usec / 1000000;
  return seconds;
}

int main (int argc, char**args) {

  // Prepare input and output buffers for tests
  const int N1 = 10000;
  float* srcdata  = (float*)malloc(N1*sizeof(float));
  float* dstdata1 = (float*)malloc(N1*sizeof(float));
  float* dstdata2 = (float*)malloc(N1*sizeof(float));
  float params[2];
  int i,j;
  for(i = 0; i < N1; i++)
    srcdata[i] = 0.7 * i;
  params[0] = 1.3;
  params[1] = 1.9;

  int N2 = 80000;
  double time1;

  // Run both transform_std and transform_opt without timing
  // measurements first, to get rid of any initialization effects.
  for(j = 0; j < N2; j++)
    transform_std (dstdata1, srcdata, params, N1);
  for(j = 0; j < N2; j++)
    transform_opt (dstdata2, srcdata, params, N1);

  // Test transform_std
  time1 = get_wall_seconds();
  for(j = 0; j < N2; j++)
    transform_std (dstdata1, srcdata, params, N1);
  printf("transform_std tests took %7.3f wall seconds.\n", get_wall_seconds()-time1);

  // Test transform_opt
  time1 = get_wall_seconds();
  for(j = 0; j < N2; j++)
    transform_opt (dstdata2, srcdata, params, N1);
  printf("transform_opt tests took %7.3f wall seconds.\n", get_wall_seconds()-time1);
  
  // Check that results are the same
  double max_abs_diff = 0;
  for(i = 0; i < N1; i++) {
    double abs_diff = fabs(dstdata2[i] - dstdata1[i]);
    if(abs_diff > max_abs_diff)
      max_abs_diff = abs_diff;
  }
  printf("Checking correctness: max_abs_diff = %8.4g\n", max_abs_diff);
  if(max_abs_diff > 1e-12) {
    printf("\nERROR: max_abs_diff too large, result seems wrong.  :-/\n\n");
    return -1;
  }
  printf("OK, result seems correct.\n");

  free(srcdata);
  free(dstdata1);
  free(dstdata2);
  
  return 0;
}

