#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define NUM_THREADS	8

pthread_mutex_t lock;
int waiting = 0;
int state = 0;

void barrier() {
  int mystate;
  pthread_mutex_lock (&lock);
  mystate=state;
  waiting++;
  if (waiting==NUM_THREADS) {
    waiting=0; state=1-mystate;
  }
  pthread_mutex_unlock (&lock);
  while (mystate==state) ;
}

void* HelloWorld(void* arg) {
  long id=(long)arg;
  printf("Hello World! %ld\n", id);
  barrier();
  printf("Bye Bye World! %ld\n", id);
  return NULL;
}

int main(int argc, char *argv[]) {
  pthread_t threads[NUM_THREADS];
  long t;
  // Initializa things
  pthread_mutex_init(&lock,NULL);
  // Create threads
  for(t=0 ; t<NUM_THREADS; t++)
    pthread_create(&threads[t], NULL, HelloWorld, (void*)t);
  // Wait for threads to finish
  for(t=0 ; t<NUM_THREADS; t++)
    pthread_join(threads[t], NULL);
  // Cleanup
  pthread_mutex_destroy(&lock);
  // Done!
  return 0;
}
