#include <stdio.h>
#include <stdlib.h>

long int sum = 0;
int N = 100000;

void the_thread_func() {

  for(int i = 1; i <= N; ++i) {
    sum += 1;
  }

}

int main(int argc, char **argv) {

  if(argc != 2) {printf("Usage: %s N\n", argv[0]); return -1; }
  int nThreads = atoi(argv[1]);

  printf("This is the main() function before the parallel block, nThreads = %d\n", nThreads);

#pragma omp parallel num_threads(nThreads)
  the_thread_func();
  
  printf("This is the main() function after the parallel block\n");

  printf("sum = %ld\n", sum);

  return 0;
}
