#include <stdio.h>
#include <pthread.h>

void* the_thread_func_B(void* arg) {
  printf("The thread function B is starting doing some work\n");
  long int k;
  double sum3;
  for(k = 0; k < 10000000000; k++) sum3 += 3e-7;
  printf("Result of work done in the thread function B: sum3 = %lf\n",sum3);
  return NULL;
}

void* the_thread_func_A(void* arg) {
  printf("The thread function A is starting doing some work\n");
  long int j;
  double sum2;
  for(j = 0; j < 10000000000; j++) sum2 += 2e-7;
  printf("Result of work done in the thread function A: sum2 = %lf\n",sum2);
  return NULL;
}

int main() {
  printf("This is the main() function starting.\n");

  /* Start thread. */
  pthread_t thread;
  pthread_t thread2;
  printf("the main() function now calling pthread_create().\n");
  pthread_create(&thread, NULL, the_thread_func_A, NULL);
  pthread_create(&thread2, NULL, the_thread_func_B, NULL);

  printf("This is the main() function after pthread_create()\n");

  printf("Main starting to do some work!\n");
  long int i;
  double sum;
  for(i = 0; i < 10000000000; i++) sum += 1e-7;
  printf("Result of work done in main(): sum = %lf\n",sum);

  /* Wait for thread to finish. */
  printf("the main() function now calling pthread_join().\n");
  pthread_join(thread, NULL);
  pthread_join(thread2, NULL);

  return 0;
}
