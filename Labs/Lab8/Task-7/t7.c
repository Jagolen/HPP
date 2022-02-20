#include <stdio.h>
#include <pthread.h>

void* treadfunc2(void* arg){
    printf("A thread was initialized by a thread!\n");
    return NULL;
}

void* treadfunc1(void* arg){
    printf("A thread was initialized by main!\n");
    printf("A thread is now creating two threads...\n");
    pthread_t thread;
    pthread_create(&thread,NULL,treadfunc2,NULL);
    pthread_create(&thread,NULL,treadfunc2,NULL);
    pthread_join(thread,NULL);
    printf("A thread is joining the two threads\n");
    return NULL;
}

int main(){
    printf("Main is now creating two threads...\n");
    pthread_t thread;
    pthread_create(&thread,NULL,treadfunc1,NULL);
    pthread_create(&thread,NULL,treadfunc1,NULL);
    pthread_join(thread,NULL);
    printf("Main joining the two threads\n");
    return 0;
}