#include <stdio.h>
#include <stdlib.h>

int main() {
  int k, n;
  double d = 1.0;
  int N = 20000000;
  double** ptrList;
  ptrList = (double**)malloc(N*sizeof(double*));
  for(k = 0; k < 3; k++)
    {
      for(n = 0; n < N; n++)
	{
	  ptrList[n] = malloc(1*sizeof(double));
	  double* p = ptrList[n];
	  *p = d + 0.0000000000001;
	  d = *p;
	}
      for(n = 0; n < N; n++)
	{
	  free(ptrList[n]);
	}
    }
  printf("%20.13f\n", d);
  free(ptrList);
  return 0;
}
