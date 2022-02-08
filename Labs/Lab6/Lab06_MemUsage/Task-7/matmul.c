#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
 
static double get_wall_seconds() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  double seconds = tv.tv_sec + (double)tv.tv_usec / 1000000;
  return seconds;
}
int rand_int(int N)
{
  int val = -1;
  while( val < 0 || val >= N )
    {
      val = (int)(N * (double)rand()/RAND_MAX);
    }
  return val;
}

void allocate_mem(int*** arr, int n)
{
  int i;
  *arr = (int**)malloc(n*sizeof(int*));
  for(i=0; i<n; i++)
    (*arr)[i] = (int*)malloc(n*sizeof(int));
}

void free_mem(int** arr, int n)
{
  int i;
  for(i=0; i<n; i++)
    free(arr[i]);
  free(arr);
}

/* kij */
void mul_kij(int n, int **a, int **b, int **c)
{
  int i, j, k;
  for (k=0; k<n; k++) {
    for (i=0; i<n; i++) {
      int x = a[i][k];
      for (j=0; j<n; j++)
	c[i][j] += x * b[k][j];   
    }
  }
}

/* ijk */
void mul_ijk(int n, int **a, int **b, int **c)
{
  int i, j, k;
  for (i=0; i<n; i++)  {
    for (j=0; j<n; j++) {
      int sum = 0;
      for (k=0; k<n; k++) 
	sum += a[i][k] * b[k][j];
      c[i][j] = sum;
    }
  }
}

/* jik */
void mul_jik(int n, int **a, int **b, int **c)
{
  int i, j, k;
  for (j=0; j<n; j++) {
    for (i=0; i<n; i++) {
      int sum = 0;
      for (k=0; k<n; k++)
	sum += a[i][k] * b[k][j];
      c[i][j] = sum;
    }
  }
}

/* kji */
void mul_kji(int n, int **a, int **b, int **c)
{
  int i, j, k;
  for (k=0; k<n; k++) {
    for (j=0; j<n; j++) {
      int sum = 0;
      for (i=0; i<n; i++)
	sum += a[i][k] * b[k][j];
      c[i][j] = sum;
    }
  }
}

/* jki */
void mul_jki(int n, int **a, int **b, int **c)
{
  int i, j, k;
  for (j=0; j<n; j++) {
    for (k=0; k<n; k++) {
      int sum = 0;
      for (i=0; i<n; i++)
	sum += a[i][k] * b[k][j];
      c[i][j] = sum;
    }
  }
}

/* ikj */
void mul_ikj(int n, int **a, int **b, int **c)
{
  int i, j, k;
  for (i=0; i<n; i++) {
    for (k=0; k<n; k++) {
      int sum = 0;
      for (j=0; j<n; j++)
	sum += a[i][k] * b[k][j];
      c[i][j] = sum;
    }
  }
}

/* ikj optimized */
void mul_ikj_optim(int n, int **a, int **b, int **c){
  int i,j,k;
  const int blockSz = 500;
  if(n % blockSz != 0) {
    printf("Error: n not divisible by blockSz.\n");
    return;
  }
  int bi, bk;
  for(i=0;i<n;i+=blockSz){
    for(k=0;k<n;k+=blockSz){
      for(bi = i; bi<i+blockSz;bi++){
        for(bk = k; bk<k+blockSz;bk++){
          int x = a[bi][bk];
          for(j=0;j<n;j++) c[bi][j] +=  x*b[bk][j];
        }
      }
    }
  }
}





/* void mul_ikj_optim(int n, int **a, int **b, int **c){
  const int blockSz = 300;
  double SubMat[blockSz*blockSz];
  if(n % blockSz != 0) {
    printf("Error: N not divisible by blockSz.\n");
    return;
  }
  int nBlocks = n / blockSz;
  int i,j,k,bi,bk;
  for(bi = 0; bi<nBlocks; bi++){
    int istart = bi*blockSz;
    for(bk = 0; bk<nBlocks; bk++){
      int kstart = bk*blockSz;
      for(i = 0; i<blockSz; i++){
        for(k = 0; k<blockSz; k++){
          int sum = a[bi][bk];
          for(j = 0; j<n;j++) c[istart+i][j] += sum*b[kstart+k][j];
        }
      }
    }
  }
}
 */
int main()
{
  int i, j, n;
  int **a;
  int **b;
  int **c;
  double time;
  int Nmax = 100; // random numbers in [0, N]

  printf("Enter the dimension of matrices n = ");
  if(scanf("%d", &n) != 1) {
    printf("Error in scanf.\n");
    return -1;
  }

  allocate_mem(&a, n);

  for ( i = 0 ; i < n ; i++ )
    for ( j = 0 ; j < n ; j++ )
      a[i][j] = rand_int(Nmax);

  allocate_mem(&b, n);
 
  for ( i = 0 ; i < n ; i++ )
    for ( j = 0 ; j < n ; j++ )
      b[i][j] = rand_int(Nmax);

  allocate_mem(&c, n);

 /*  time=get_wall_seconds();
  mul_kij(n, a, b, c);
  time=get_wall_seconds()-time;
  printf("Version kij, time = %f\n",time);
  time=get_wall_seconds();
  mul_ijk(n, a, b, c);
  time=get_wall_seconds()-time;
  printf("Version ijk, time = %f\n",time);
  time=get_wall_seconds();
  mul_jik(n, a, b, c);
  time=get_wall_seconds()-time;
  printf("Version jik, time = %f\n",time); */
  time=get_wall_seconds();
  mul_ikj_optim(n, a, b, c);
  time=get_wall_seconds()-time;
  printf("Version ikj optimized, time = %f\n",time);
  /* time=get_wall_seconds();
  mul_kji(n, a, b, c);
  time=get_wall_seconds()-time;
  printf("Version kji, time = %f\n",time);
  time=get_wall_seconds();
  mul_jki(n, a, b, c);
  time=get_wall_seconds()-time;
  printf("Version jki, time = %f\n",time);
  time=get_wall_seconds();
  mul_ikj(n, a, b, c);
  time=get_wall_seconds()-time;
  printf("Version ikj, time = %f\n",time);*/

  /*
    printf("Product of entered matrices:\n");
 
    for ( i = 0 ; i < n ; i++ )
    {
    for ( j = 0 ; j < n ; j++ )
    printf("%d\t", c[i][j]);
 
    printf("\n");
    }
  */

  free_mem(a, n);
  free_mem(b, n);
  free_mem(c, n);

  return 0;
}
