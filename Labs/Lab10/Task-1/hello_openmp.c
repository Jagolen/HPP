#include <stdio.h>
#include <omp.h>

int main(int argc, char** argv) {
omp_set_num_threads(7);

#pragma omp parallel
  {
    printf("Bonjour!\n");
  }

  return 0;
}
