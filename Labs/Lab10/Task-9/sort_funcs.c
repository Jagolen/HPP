#include <stdlib.h>
#include <omp.h>
#include "sort_funcs.h"
#include <stdio.h>

void bubble_sort(intType* list, int N) {
  int i, j;
  for(i = 0; i < N-1; i++)
    for(j = 1+i; j < N; j++) {
      if(list[i] > list[j]) {
	// Swap
	intType tmp = list[i];
	list[i] = list[j];
	list[j] = tmp;
      }
    }
}

void merge_sort(intType* list_to_sort, int N, int nthreads) {
  if(N == 1) {
    // Only one element, no sorting needed. Just return directly in this case.
    return;
  }
  //printf("NThreads is %d\n",nthreads);
  int n1 = N / 2;
  int n2 = N - n1;
  // Allocate new lists
  intType* list1 = (intType*)malloc((n1+n2)*sizeof(intType));
  intType* list2 = &list1[n1];
  int i;
  for(i = 0; i < n1; i++)
    list1[i] = list_to_sort[i];
  for(i = 0; i < n2; i++)
    list2[i] = list_to_sort[n1+i];
  // Sort list1 and list2
  
  if(nthreads <= 1){
    //printf("Only one thread\n");
    merge_sort(list1, n1,nthreads/2);
    merge_sort(list2, n2,nthreads/2);
  }
  else{
    #pragma omp parallel num_threads(2)
    {
      //printf("Creating two threads!\n");
      if(omp_get_thread_num()==0) merge_sort(list1, n1,nthreads/2);
      else merge_sort(list2, n2,nthreads/2);
    }
  }

  // Merge!
  int i1 = 0;
  int i2 = 0;
  i = 0;
  while(i1 < n1 && i2 < n2) {
    if(list1[i1] < list2[i2]) {
      list_to_sort[i] = list1[i1];
      i1++;
    }
    else {
      list_to_sort[i] = list2[i2];
      i2++;
    }
    i++;
  }
  while(i1 < n1)
    list_to_sort[i++] = list1[i1++];
  while(i2 < n2)
    list_to_sort[i++] = list2[i2++];
  free(list1);
}

