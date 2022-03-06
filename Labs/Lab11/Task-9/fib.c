#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

long int Fib(int n, int threads) {
  long int i1 = 0;
  long int i2 = 0;
  if(n < 2) 
    return n;
  if(threads <=1 ){
  i1 = Fib(n-1,1);
  i2 = Fib(n-2,1);
  return i1 + i2;
  }
  else{
    #pragma omp parallel num_threads(2)
    {
      if(omp_get_thread_num()==0) i1 = Fib(n-1,threads/2);
      else i2 = Fib(n-2,threads/2);
    }
    return i1+i2;
  }
  
}

int main(int argc, char** argv) {
  if(argc != 3) {
    printf("Please give two input arg: n, threads\n");
    return -1;
  }
  int n = atoi(argv[1]);
  int threads = atoi(argv[2]);
  omp_set_nested(1);
  printf("n = %d\n", n);
  long int Fib_of_n = Fib(n,threads);
  printf("Fib(%d) = %ld\n", n, Fib_of_n);
  return 0;
}
