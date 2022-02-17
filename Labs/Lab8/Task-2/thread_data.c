#include <stdio.h>
#include <pthread.h>

void* the_thread_func(void* arg) {
  double* ptr = (double*) arg;
  printf("Data for thread contains: [%lf, %lf, %lf]\n",ptr[0],ptr[1],ptr[2]);
  return NULL;
}

int main() {
  printf("This is the main() function starting.\n");

  double data_for_thread[3];
  data_for_thread[0] = 5.7;
  data_for_thread[1] = 9.2;
  data_for_thread[2] = 1.6;

  double data_for_thread2[3];
  data_for_thread2[0] = 56.7;
  data_for_thread2[1] = 90.2;
  data_for_thread2[2] = 12.6;
 

  /* Start thread. */
  pthread_t thread;
  printf("the main() function now calling pthread_create().\n");
  pthread_create(&thread, NULL, the_thread_func, data_for_thread);
  pthread_create(&thread,NULL,the_thread_func,data_for_thread2);

  printf("This is the main() function after pthread_create()\n");

  /* Do something here? */

  /* Wait for thread to finish. */
  printf("the main() function now calling pthread_join().\n");
  pthread_join(thread, NULL);

  return 0;
}
