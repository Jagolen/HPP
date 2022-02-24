#include <stdio.h>
#include <omp.h>

void thread_func() {
  printf("This is inside thread_func()!\n");
}

int main(int argc, char** argv) {

#pragma omp parallel num_threads(4)
  {
    thread_func();
  }

  return 0;
}
