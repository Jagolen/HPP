#include <stdio.h>

int main(int argc, char *argv[]) {
  const int N = 4;
  int list[N];

#pragma omp parallel for
  for(int i = 0; i < N; i++)
    list[i] = i*i;

  for(int i = 0; i < N; i++)
    printf("list[%d] = %d\n", i, list[i]);

  return 0;
}
