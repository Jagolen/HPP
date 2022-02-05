#include<stdio.h>

float arr[100];
int size=100;

int main()
{
  int i, k;
  float sum = 0.0;
  int N = 100000000;
  /* This is no interesting computation, just something to make the program bysy. */
  for(k = 0; k < N; k++) {
    arr[0] = 1;
    for(i=1; i<size; i++)
      {
        arr[i] = 0.5*arr[i-1];
        sum += arr[i];
      }
  }
  printf("Done! sum = %f\n", sum);
  return 0;
}
