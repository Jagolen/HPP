#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <string.h>
#include <math.h>
#include "stencil.h"

static double get_wall_seconds() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  double seconds = tv.tv_sec + (double)tv.tv_usec / 1000000;
  return seconds;
}

static void printGrid(const GridPt* grid, int N) {
  int printing_enabled = 0;
  if(printing_enabled) {
    int i, j;
    for(i = 0; i < N; i++) {
      for(j = 0; j < N; j++)
	printf("%6.2f ", grid[i*N+j].x);
      printf("\n");
    }
    printf("\n");
  }
}

void setup_guess(GridPt* guess, int N) {
  // Initialize guess to zero inside and 1 along borders
  int i, j;
  // First set 1 everywhere
  for(i = 0; i < N*N; i++)
    guess[i].x = 1;
  // Now set inner part to zero
  for(i = STENCIL_SZ; i < N-STENCIL_SZ; i++)
    for(j = STENCIL_SZ; j < N-STENCIL_SZ; j++)
      guess[i*N+j].x = 0;
}

void apply_stencil_function(const GridPt* grid_src, GridPt* grid_dst, int N, int functionVersion) {
  if(functionVersion == 1)
    apply_stencil_v1(grid_src, grid_dst, N);
  else if(functionVersion == 2)
    apply_stencil_v2(grid_src, grid_dst, N);
  else if(functionVersion == 3)
    apply_stencil_v3(grid_src, grid_dst, N);
  else
    printf("ERROR in apply_stencil_function: functionVersion %d not recognized.\n", functionVersion);
}

void do_iterations(int N, const GridPt* guess, GridPt* resultBuf, int nIters, int functionVersion, int do_print) {
  GridPt* buf1 = (GridPt*)malloc(N*N*sizeof(GridPt));
  GridPt* buf2 = (GridPt*)malloc(N*N*sizeof(GridPt));
  GridPt* grid1;
  GridPt* grid2;
  memcpy(buf1, guess, N*N*sizeof(GridPt));
  memcpy(buf2, guess, N*N*sizeof(GridPt));
  grid1 = buf1;
  grid2 = buf2;
  double time1 = get_wall_seconds();
  int i;
  for(i = 0; i < nIters; i++) {
    apply_stencil_function(grid1, grid2, N, functionVersion);
    // Now the updated grid is in grid2. Switch.
    GridPt* tmp = grid1;
    grid1 = grid2;
    grid2 = tmp;
  }
  printGrid(grid1, N);
  if(do_print == 1)
    printf("Doing %d iterations with N=%d using apply_stencil function version %d took %7.3f wall seconds.\n", nIters, N, functionVersion, get_wall_seconds()-time1);
  memcpy(resultBuf, grid1, N*N*sizeof(GridPt));
  free(buf1);
  free(buf2);
}

int verify_results(int N, GridPt* grid1, int v1, GridPt* grid2, int v2) {
  double max_abs_diff = 0;
  int i;
  for(i = 0; i < N*N; i++) {
    double abs_diff = fabs(grid2[i].x - grid1[i].x);
    if(abs_diff > max_abs_diff)
      max_abs_diff = abs_diff;
  }
  printf("Checking correctness by comparing %d and %d: max_abs_diff = %8.4g\n", v1, v2, max_abs_diff);
  if(max_abs_diff > 1e-12) {
    printf("\nERROR: max_abs_diff too large, result seems wrong.  :-/\n\n");  
    return -1;
  }
  return 0;
}

int main (int argc, char**args) {

  //  int N = 286;
  //  int N = 542;
  int N = 192 + 2*STENCIL_SZ;

  GridPt* guess = (GridPt*)malloc(N*N*sizeof(GridPt));

  setup_guess(guess, N);

  printGrid(guess, N);

  GridPt* result1 = (GridPt*)malloc(N*N*sizeof(GridPt));
  GridPt* result2 = (GridPt*)malloc(N*N*sizeof(GridPt));
  GridPt* result3 = (GridPt*)malloc(N*N*sizeof(GridPt));

  const int nIters = 400;

  // First run without printing timings, to get rid of any startup effect that could make the comparison unfair.
  int do_print = 0;
  do_iterations(N, guess, result1, nIters, 1, do_print);
  do_iterations(N, guess, result2, nIters, 2, do_print);
  do_iterations(N, guess, result3, nIters, 3, do_print);
  // Now run with printing timings.
  do_print = 1;
  do_iterations(N, guess, result1, nIters, 1, do_print);
  do_iterations(N, guess, result2, nIters, 2, do_print);
  do_iterations(N, guess, result3, nIters, 3, do_print);

  // To check correctness, compare results of apply_stencil_optimized and apply_stencil_standard for final grid.
  if(verify_results(N, result1, 1, result2, 2) != 0)
    return -1;
  if(verify_results(N, result1, 1, result3, 3) != 0)
    return -1;

  printf("OK, results seem correct!\n");

  free(guess);
  free(result1);
  free(result2);
  free(result3);
  
  return 0;
}

