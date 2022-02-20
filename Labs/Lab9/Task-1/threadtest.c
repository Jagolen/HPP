#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void* the_thread_func(void* arg) {
  /* Do something here? */
  int *dynarr = (int*)malloc(10*sizeof(int));
  for(int i = 0; i<10; i++) dynarr[i] = i*3;
  return (void*)dynarr;
}

int main() {
  printf("This is the main() function starting.\n");

  /* Start thread. */
  pthread_t thread;

  printf("the main() function now calling pthread_create().\n");
  if(pthread_create(&thread, NULL, the_thread_func, NULL) != 0) {
    printf("ERROR: pthread_create failed.\n");
    return -1;
  }

  printf("This is the main() function after pthread_create()\n");

  /* Do something here? */

  /* Wait for thread to finish. */
  printf("the main() function now calling pthread_join().\n");
  void *fromthread;
  if(pthread_join(thread, &fromthread) != 0) {
    printf("ERROR: pthread_join failed.\n");
    return -1;
  }
  int *ft = (int*) fromthread;
  for(int i = 0; i<10; i++) printf("%d\n",ft[i]);
  free(fromthread);
  return 0;
}
