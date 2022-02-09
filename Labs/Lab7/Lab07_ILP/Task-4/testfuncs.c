#include "testfuncs.h"

double f_std(const double * a, int N) {
  int i;
  double sum = 0;
  int counter = 0;
  for(i = 0; i < N; i++) {
    if(a[i] > 0.5 && counter == 3)
      sum += 0.1*a[i];
    if(counter > 5 && a[i] > 0.5)
      counter = 5;
    if(counter > 6 && a[i] > 0.6)
      counter = 6;
    sum += 0.3*a[i] + a[i]*a[i];
    counter++;
  }
  return sum;
}

double f_opt(const double * a, int N) {
  int i;
  double sum = 0;
  sum += 0.3*a[0] + a[0]*a[0];
  sum += 0.3*a[1] + a[1]*a[1];
  sum += 0.3*a[2] + a[2]*a[2];
  sum += 0.1*a[3];
  sum += 0.3*a[3] + a[3]*a[3];
  for(i = 4; i < N; i++) sum += 0.3*a[i] + a[i]*a[i];
  return sum;
}

