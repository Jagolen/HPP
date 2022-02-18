#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>

static double get_wall_seconds() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  double seconds = tv.tv_sec + (double)tv.tv_usec / 1000000;
  return seconds;
}

int isprime(int n){
    for(int i = 2; i<n; i++){
        if(n%i == 0) return 0;
    }
    return 1;
}

void* thread_A(void* arg) {
  printf("Thread A starting\n");
  int sum_thread = 0;
  int M = *((int*)arg);
  for(int i=5;i<M;i+=4){
      sum_thread += isprime(i);
  }
  int *sumptr; 
  sumptr = (int*)arg;
  *sumptr = sum_thread;
  return NULL;
}

int main(int argc, char* argv[]){
    if(argc != 2) {
        printf("Exactly one input please.\n");
        return -1;
    }
    int M = atoi(argv[1]);
    int input = M;

    pthread_t thread;
    printf("Main thread starting\n");
    double tot_time = get_wall_seconds();
    pthread_create(&thread,NULL,thread_A,&input);
    int sum_main = 1;
    for(int i=3;i<M;i+=4){
        sum_main += isprime(i);
    }
    printf("Main thread done\n");
    pthread_join(thread,NULL);
    tot_time = get_wall_seconds() - tot_time;
    printf("Work took %lf wall seconds\n",tot_time);
    int sum = sum_main + input;
    printf("There are %d prime numbers under %d!\n",sum,M);
}