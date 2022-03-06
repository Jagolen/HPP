/**********************************************************************
 * This program calculates pi using C
 *
 **********************************************************************/
#include <stdio.h>

int main(int argc, char *argv[]) {

  int i;
  const int intervals = 500000000;
  double sum, dx, x;
  int threads = 4;
  dx  = 1.0/intervals;
  sum = 0.0;
  #pragma omp parallel for schedule(static) reduction(+:sum) num_threads(threads)
    for (i = 1; i <= intervals; i++) {
      x = dx*(i - 0.5);
      sum += dx*4.0/(1.0 + x*x);
    }

  printf("PI is approx. %.16f\n",  sum);

  return 0;
}
