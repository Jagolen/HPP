#include <stdio.h>
#include <pthread.h>

double thread_work_result = 0;

void* the_thread_func(void* arg) {
  int k;
  double d = 1.0;
  for(k = 0; k < 500000000; k++)
    {
      d *= 1.0000000000001;
    }
  thread_work_result = d;
  return NULL;
}

int main() {
  /* Start thread. */
  pthread_t thread;
  pthread_create(&thread, NULL, the_thread_func, NULL);
  /* Let main thread do some work. */
  int k;
  double d = 1.0;
  for(k = 0; k < 500000000; k++)
    {
      d *= 1.0000000000001;
    }
  /* Wait for thread to finish. */
  pthread_join(thread, NULL);
  /* Print results. */
  printf("main thread result : %20.13f\n", d);
  printf("other thread result: %20.13f\n", thread_work_result);
  return 0;
}
