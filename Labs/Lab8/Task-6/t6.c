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

typedef struct threadinfo{
    int index;
    int sum;
    int N;
    int M;
} t_info;

int isprime(int n){
    for(int i = 2; i<n; i++){
        if(n%i == 0) return 0;
    }
    return 1;
}

void* thread_A(void* arg) {
    t_info *tinf = (t_info*)arg;
    int M = tinf->M;
    int N = tinf->N;
    int sum = tinf->sum;
    int index = tinf->index;
    printf("Thread %d starts working\n",index);
    for(int i = 5 + index*2;i<M;i+=((N+1)*2)){
        sum += isprime(i);
    }
    tinf->sum = sum;
    printf("Thread %d done!\n",index);
  return NULL;
}

int main(int argc, char* argv[]){
    if(argc != 3) {
        printf("Exactly two inputs please.\n");
        return -1;
    }
    int M = atoi(argv[1]);
    int N = atoi(argv[2]);
    t_info arr[N];
    pthread_t thread;
    printf("Main thread starting\n");
    double tot_time = get_wall_seconds();
    for(int i=0;i<N;i++){
        arr[i].index = i;
        arr[i].M = M;
        arr[i].N = N;
        arr[i].sum = 0;
        pthread_create(&thread,NULL,thread_A,&arr[i]);
    }

    int sum_main = 1;
    for(int i=3;i<M;i+=((N+1)*2)){
        sum_main += isprime(i);
    }
    printf("Main thread done\n");
    pthread_join(thread,NULL);
    int sum = sum_main;
    for(int i = 0;i<N;i++){
        sum += arr[i].sum;
    }
    tot_time = get_wall_seconds() - tot_time;
    printf("Work took %lf wall seconds\n",tot_time);
    printf("There are %d prime numbers under %d!\n",sum,M);
}