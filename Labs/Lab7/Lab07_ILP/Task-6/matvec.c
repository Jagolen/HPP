#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <sys/time.h>
 
static double get_wall_seconds() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  double seconds = tv.tv_sec + (double)tv.tv_usec / 1000000;
  return seconds;
}


/* TASK: Ensure that this matrix multiplication is autovectorized */
void matvec_autovec(double **mat_a,double *vec_b, double *vec_c,int SIZE)
{
    int i, j;

    for (i = 0; i < SIZE; i++)
                for (j = 0; j < SIZE; j++)
                        vec_c[i] += mat_a[i][j] * vec_b[j];
}

/* Don't change this */
void matvec_ref(double **mat_a,double *vec_b, double *vec_c,int SIZE)
{
    int i, j;

    for (i = 0; i < SIZE; i++)
                for (j = 0; j < SIZE; j++)
                        vec_c[i] += mat_a[i][j] * vec_b[j];
}

/**
 * Function used to verify the result. No need to change this one.
 */
int verify_result(double *vec_c,double *vec_ref,int SIZE)
{
    float e_sum;
    int i;

    e_sum = 0;
    for (i = 0; i < SIZE; i++) {
            e_sum += vec_c[i] < vec_ref[i] ?
                    vec_ref[i] - vec_c[i] :
                    vec_c[i] - vec_ref[i];
    }


  printf("e_sum: %f\n", e_sum);
  return e_sum < 1E-6;
}

void allocate_mat(double*** arr, int n)
{
  int i;
  *arr = (double**)malloc(n*sizeof(double*));
  for(i=0; i<n; i++)
    (*arr)[i] = (double*)malloc(n*sizeof(double));
}

void free_mat(double** arr, int n)
{
  int i;
  for(i=0; i<n; i++)
    free(arr[i]);
  free(arr);
}

void init_matvec(double **mat_a,double *vec_b,
                   double *vec_c,double *vec_d,int SIZE)
{
  int i, j;

  for (i = 0; i < SIZE; i++) {
    for (j = 0; j < SIZE; j++)
        mat_a[i][j] = drand48();
      vec_b[i] = drand48();
      vec_c[i] = 0.0;
      vec_d[i] = 0.0;
  
  }
}


int
main(int argc, char *argv[])
{
  /* Initialize the matrices with some "random" data. */
    const int SIZE=16384;
    double **a,*b,*c,*d;
    double time1,time2;
    allocate_mat(&a,SIZE);
    b=(double*)malloc(SIZE*sizeof(double));
    c=(double*)malloc(SIZE*sizeof(double));
    d=(double*)malloc(SIZE*sizeof(double));
    init_matvec(a,b,c,d,SIZE);
    
    time1=get_wall_seconds();
    matvec_ref(a,b,d,SIZE);
    time1=get_wall_seconds()-time1;
    printf("Ref: time = %f\n",time1);
    time2=get_wall_seconds();
    matvec_autovec(a,b,c,SIZE);
    time2=get_wall_seconds()-time2;
    printf("Auto-vec: time = %f\n",time2);
    
    if (verify_result(c,d,SIZE))
      printf("OK\n");
    else
      printf("MISMATCH\n");
    free_mat(a,SIZE);
    free(b);free(c);free(d);

  return 0;
}

