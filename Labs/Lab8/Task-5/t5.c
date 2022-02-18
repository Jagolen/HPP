#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>


typedef struct threadinfo{
    int index;
} t_info;

void* thread_A(void* arg) {
    t_info *tinf = (t_info*)arg;
    int index = tinf->index;
    printf("Thread %d was activated\n",index);
    return NULL;
}

int main(int argc, char* argv[]){
    if(argc != 2) {
        printf("Exactly one input please.\n");
        return -1;
    }
    int numthreads = atoi(argv[1]);
    printf("Creating %d threads\n",numthreads);
    pthread_t thread;
    t_info arr[numthreads];

    for(int i=0;i<numthreads;i++){
        arr[i].index = i;
        pthread_create(&thread,NULL,thread_A,&arr[i]);
    }
    printf("Joining the threads\n"); 
    pthread_join(thread,NULL);
    return 0;
}