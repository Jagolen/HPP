#include <omp.h>
#include <stdio.h>

void fun2(){
    printf("inside fun2 with id %d\n",omp_get_thread_num());
}

void fun1(){
    printf("Inside fun1 with id %d\n",omp_get_thread_num());
    #pragma omp parallel num_threads(2)
    fun2();
}

int main(){
    omp_set_nested(1);
    #pragma omp parallel num_threads(2)
    fun1();
    return 0;
}