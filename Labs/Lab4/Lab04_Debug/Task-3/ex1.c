#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int function77(int N) {
  int i, sum;
  int *arr1 = (int*)malloc(sizeof(int) * N);
  int *arr2 = (int*)malloc(sizeof(int) * N);
  for (i = 0; i < N; i++) {
    arr1[i] = i;
    arr2[i] = arr1[i] + 7;
  }
  sum = 0;
  for (i = 0; i < N; i++)
    sum += arr2[i] - arr1[i];
  free(arr1);
  free(arr2);
  return sum;
}

int function66(int N) {
  int i1 = function77(N);
  int i2 = function77(N+1);
  return i1 + i2;
}

int main(){
  int i;
  int N = 15;
  int *array = (int*)malloc(sizeof(int) * (N+1));

  /* initialize random seed */
  srand (time(NULL));

  for (i = 0; i <= N; i++){
    array[i] = rand() % 100;
  }

  for (i = 0; i < N; i++){
    printf("%d ", array[i]);
  }
  printf("\n");

  free(array);
 
  int x = function66(N);
  printf("function66 result: %d\n", x);

  return 0;
}
