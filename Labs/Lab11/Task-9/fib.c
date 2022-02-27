#include <stdio.h>
#include <stdlib.h>

long int Fib(int n) {
  if(n < 2) 
    return n;
  long int i1 = Fib(n-1);
  long int i2 = Fib(n-2);
  return i1 + i2;
}

int main(int argc, char** argv) {
  if(argc != 2) {
    printf("Please give one input arg: n\n");
    return -1;
  }
  int n = atoi(argv[1]);
  printf("n = %d\n", n);
  long int Fib_of_n = Fib(n);
  printf("Fib(%d) = %ld\n", n, Fib_of_n);
  return 0;
}
