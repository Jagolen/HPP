#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>

int isprime(int n){
    for(int i = 2; i<n; i++){
        if(n%i == 0) return 0;
    }
    return 1;
}

int main(int argc, char* argv[]){
    if(argc != 3) {
        printf("Largest number to search and number of threads.\n");
        return -1;
    }
    int M = atoi(argv[1]);
    int threads = atoi(argv[2]);
    int sum = 1;
    int input = M;
    double tot_time = omp_get_wtime();
    #pragma omp parallel for schedule(dynamic) reduction(+:sum) num_threads(threads)
        for(int i = 3; i<M; i+=2)
            sum+= isprime(i);
    tot_time = omp_get_wtime() - tot_time;
    printf("Work took %lf wall seconds\n",tot_time);
    printf("There are %d prime numbers under %d!\n",sum,M);
}