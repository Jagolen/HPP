#ifdef _OPENMP
#include <omp.h>
#endif
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

void calc_num_prime(int *sum, int M, int id,int threads) {
  printf("Thread %d starting\n",id);
  for(int i=3+2*id;i<M;i+=2*threads){
      //printf("Checking %d...\n",i);
      *sum += isprime(i);
  }
  printf("Thread %d found %d primes!\n",id,*sum);
}

int main(int argc, char* argv[]){
    if(argc != 3) {
        printf("Largest number to search and number of threads.\n");
        return -1;
    }
    int M = atoi(argv[1]);
    #ifdef _OPENMP
        int threads = atoi(argv[2]);
    #else
        int threads = 1;
    #endif
    int sum = 1;
    int input = M;
    int sum_from_threads[threads];
    printf("Thread(s) starting\n");
    #ifdef _OPENMP
        double tot_time = omp_get_wtime();
    #else
        double tot_time = get_wall_seconds();
    #endif
    #pragma omp parallel num_threads(threads)
        {
            #ifdef _OPENMP
                int id = omp_get_thread_num();
            #else
                int id = 0;
            #endif
            sum_from_threads[id] = 0;
            calc_num_prime(&sum_from_threads[id],M,id,threads);
        }
    #ifdef _OPENMP
        printf("OpenMP threads done\n");
        tot_time = omp_get_wtime() - tot_time;
    #else
        printf("Single thread done\n");
        tot_time = get_wall_seconds() - tot_time;
    #endif
    printf("Work took %lf wall seconds\n",tot_time);
    for(int i = 0;i<threads;i++) sum += sum_from_threads[i];
    printf("There are %d prime numbers under %d!\n",sum,M);
}