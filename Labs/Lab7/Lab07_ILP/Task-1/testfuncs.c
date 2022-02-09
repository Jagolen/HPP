#include "testfuncs.h"

void f_std(const double * __restrict a, 
	   const double * __restrict b, 
	   double * __restrict c, int N) {
  int i;
  double x = 0.3;
  for(i = 0; i < N; i++) {
    c[i] = a[i]*a[i] + b[i] + x;
  }
}

void f_opt(const double * __restrict a, 
	   const double * __restrict b, 
	   double * __restrict c, int N) {
  int i;
  double x = 0.3;
  for(i = 0; i < N; i++) {
    c[i] = a[i]*a[i] + b[i] + x;
  }
}

