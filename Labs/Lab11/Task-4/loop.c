#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

double work(double c){
  double d=0.0;
  int k;
  for (k=0;k<200;k++){
    d=0.0;
    while (d<c)
      d=d+1.0;
  }
  return d;
}

int main(int argc, char *argv[]) {
  int i, n = 5000;
  double *A,*B;
  double timer1;

  if(argc != 2) {
    printf("Please give 1 arg: number of threads to use.\n");
    return -1;
  }
  int nThreads = atoi(argv[1]);

  A = (double *)malloc(n*sizeof(double));
  B = (double *)malloc(n*sizeof(double));
  for (i=0;i<n;i++) {
    A[i]=(double)i;
  }

  timer1=omp_get_wtime();

#pragma omp parallel num_threads(nThreads)
  {
#pragma omp for schedule(guided)
    for (i=0;i<n;i++){
      B[i]=work(A[i]);
    }
  }

  timer1 = omp_get_wtime() - timer1;
  printf("Time taken: %f sec\n", timer1);

  /* Sum up results. */
  double sum = 0;
  int k;
  for(k = 0; k < n; k++)
    sum += B[k];

  printf("sum = %f\n", sum);

  free(A);
  free(B);

  return 0;
}
