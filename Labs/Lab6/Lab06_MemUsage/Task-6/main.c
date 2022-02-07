#include <stdio.h>
#include "func.h"

int main() {
  int n = 20000;
  int i, j;
  int sum = 0;
  for(i = 0; i < n; i++) {
    for(j = 0; j < n; j++) {
      sum += f(i) + 3*j;
    }
  }
  printf("Result sum: %d\n", sum);
  printf("Function call counter: %d\n", get_counter());
  return 0;
}

