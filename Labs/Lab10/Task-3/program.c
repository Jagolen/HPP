#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

void thread_func() {
  printf("This is inside thread_func()!\n");
  int ID = omp_get_thread_num();
  int tot = omp_get_num_threads();
  int max = omp_get_max_threads();
  printf("This is thread %d of %d\t Max is %d\n",ID,tot,max);
}

int main(int argc, char** argv) {
int n = atoi(argv[1]);

#pragma omp parallel num_threads(n)
  {
    thread_func();
  }

  return 0;
}
