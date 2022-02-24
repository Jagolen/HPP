#include <stdio.h>

int main(int argc, char** argv) {

#pragma omp parallel num_threads(5)
  {
    printf("Bonjour!\n");
  }

  return 0;
}
