/**
 * Example of using gettimeofday() to measure timings in wall clock time.
 *
 * Course: High Performance Programming, Uppsala University
 *
 * Author: Elias Rudberg <elias.rudberg@it.uu.se>
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

/* Here we define a routine called get_wall_seconds() the gets number
   of seconds and microseconds since the Epoch (1970-01-01 00:00:00
   +0000 (UTC)). The seconds and microseconds values are combined in a
   double number giving the number of seconds since the Epoch. */
static double get_wall_seconds() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  double seconds = tv.tv_sec + (double)tv.tv_usec / 1000000;
  return seconds;
}

int main(int argc, const char** argv) {
  /* Do some computations and use get_wall_seconds() to measure the time of each part. */

  /* Part 1. */
  double startTime1 = get_wall_seconds();
  int N1 = 100000;
  double sum1 = 0;
  int i;
  for(i = 0; i < N1; i++) {
    double y = 1.0 + 0.000001*i;
    sum1 += y*y / N1;
  }
  printf("sum1 = %f\n", sum1);
  double secondsTaken1 = get_wall_seconds() - startTime1;
  printf("secondsTaken1 = %f\n", secondsTaken1);

  /* Part 2. */
  double startTime2 = get_wall_seconds();
  int N2 = 1000000;
  double sum2 = 0;
  for(i = 0; i < N2; i++) {
    double y = 1.0 + 0.000001*i;
    sum2 += y*y / N2;
  }
  printf("sum2 = %f\n", sum2);
  double secondsTaken2 = get_wall_seconds() - startTime2;
  printf("secondsTaken2 = %f\n", secondsTaken2);

  /* Part 3. */
  double startTime3 = get_wall_seconds();
  int N3 = 10000000;
  double sum3 = 0;
  for(i = 0; i < N3; i++) {
    double y = 1.0 + 0.000001*i;
    sum3 += y*y / N3;
  }
  printf("sum3 = %f\n", sum3);
  double secondsTaken3 = get_wall_seconds() - startTime3;
  printf("secondsTaken3 = %f\n", secondsTaken3);

  /* Get total time. */
  double totalTimeTaken = get_wall_seconds() - startTime1;
  printf("totalTimeTaken = %f\n", totalTimeTaken);

  return 0;
}
