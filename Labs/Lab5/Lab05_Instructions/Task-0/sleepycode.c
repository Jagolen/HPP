#include <stdio.h>
#include <unistd.h>

int main() {
  int k, m;
  double d = 1.0;
  for(m = 0; m < 5; m++) {
    /* Do some work. */
    for(k = 0; k < 100000000; k++)
      {
	d *= 1.0000000000001;
      }
    /* Sleep for one second. */
    printf("Calling sleep(), m = %d\n", m);
    sleep(1);
  }
  printf("%20.13f\n", d);
  return 0;
}
