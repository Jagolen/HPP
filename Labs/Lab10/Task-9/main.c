#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "sort_funcs.h"

static double get_wall_seconds() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  double seconds = tv.tv_sec + (double)tv.tv_usec / 1000000;
  return seconds;
}

static int count_values(const intType* list, int n, intType x) {
  int count = 0;
  int i;
  for(i = 0; i < n; i++) {
    if(list[i] == x)
      count++;
  }
  return count;
}

int main(int argc, char* argv[]) {
  if(argc != 2) {
    printf("Please give 1 argument: N (number of elements to sort).\n");
    return -1;
  }
  int N = atoi(argv[1]);
  printf("N = %d\n", N);
  if(N < 1) {
    printf("Error: (N < 1).\n");
    return -1;
  }
  intType* list_to_sort = (intType*)malloc(N*sizeof(intType));
  // Fill list with random numbers
  int i;
  for(i = 0; i < N; i++)
    list_to_sort[i] = rand() % 100;

  // Count how many times the number 7 exists in the list.
  int count7 = count_values(list_to_sort, N, 7);
  printf("Before sort: the number 7 occurs %d times in the list.\n", count7);

  // Sort list
  double time1 = get_wall_seconds();
  merge_sort(list_to_sort, N);
  printf("Sorting list with length %d took %7.3f wall seconds.\n", N, get_wall_seconds()-time1);  

  int count7_again = count_values(list_to_sort, N, 7);
  printf("After sort : the number 7 occurs %d times in the list.\n", count7_again);

  // Check that list is really sorted
  for(i = 0; i < N-1; i++) {
    if(list_to_sort[i] > list_to_sort[i+1]) {
      printf("Error! List not sorted!\n");
      return -1;
    }
  }
  printf("OK, list is sorted!\n");

  free(list_to_sort);

  return 0;
}
