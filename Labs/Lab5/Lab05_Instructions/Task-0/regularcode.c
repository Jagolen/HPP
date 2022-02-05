#include <stdio.h>

int main() {
  int k;
  double d = 1.0;
  for(k = 0; k < 500000000; k++)
    {
      d *= 1.0000000000001;
    }
  printf("%20.13f\n", d);
  return 0;
}
