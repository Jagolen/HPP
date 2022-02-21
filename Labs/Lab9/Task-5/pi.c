/**********************************************************************
 * This program calculates pi using C
 *
 **********************************************************************/
#include <stdio.h>
#include <pthread.h>

typedef struct to_thread{
  int index;
  double sum;
  int subint;
  double dx;
} to_t;

void* threadfun(void *arg){
  to_t *arr = (to_t*) arg;
  double x;
  int subint = arr->subint;
  int index = arr->index;
  double sum = arr->sum;
  double dx = arr->dx;
  //printf("Thread %d calculating integral from %d to %d\n",index,subint*index+1,subint*(index+1));
  for(int i = subint*index+1; i<subint*(index+1);i++){
    x = dx*(i - 0.5);
    sum += dx*4.0/(1.0 + x*x);  
  }
  arr->sum = sum;
  //printf("Sum from thread %d = %lf\n",index,sum);
  return NULL;
}

int main(int argc, char *argv[]) {

  int i;
  const int intervals = 500000000;
  int subinterval = intervals / 4;
  double sum, dx, x;
  pthread_t thread[3];
  dx  = 1.0/intervals;
  sum = 0.0;
  to_t input[3];
  for(int j = 0; j<3; j++){
    input[j].index = j+1;
    input[j].sum = 0;
    input[j].subint = subinterval;
    input[j].dx = dx;
    pthread_create(&thread[j],NULL,threadfun,&input[j]);
  }

  for (i = 1; i <= subinterval; i++) { 
    x = dx*(i - 0.5);
    sum += dx*4.0/(1.0 + x*x);
  }
  printf("sum from main = %lf\n",sum);
  pthread_join(thread[0],NULL);
  pthread_join(thread[1],NULL);
  pthread_join(thread[2],NULL);
  for(int k = 0; k<3; k++) sum += input[k].sum;
  printf("PI is approx. %.16f\n",  sum);
  return 0;
}
