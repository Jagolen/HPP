#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
 * Sort an array using bubble sort algorithm.
 */

/* Swap values pointed by x and y */
void swap(int *x, int *y)
{
   int tmp;

   tmp = *x;
   *x  = *y;
   *y  = tmp;
}


void print_array(int *a, int n)
{
   for (int i = 0; i < n; i++)
   {
      printf("%d ", a[i]);
   }
   printf("\n");
}


void fill_in_array(int *a, int n)
{
   srand(time(NULL));
   for (int i = 0; i < n; ++i)
   {
      a[i] = rand() % n;
   }
}


void bubble_sort(int *a, int n)
{
   int swapped = 0;

   for (int i = 0; i < n; ++i)
   {
      swapped = 0;
      // avoid looking at the last n-1 items when running for the n-th time
      for (int k = 1; k < n-i; ++k)
      {
         if (a[k] < a[k - 1])
         {
            swap(&a[k], &a[k - 1]);
            swapped = 1;
         }
      }
      if (swapped == 0)
          break;
   }
}


int main(int argc, char const *argv[])
{
   int n;

   if (argc != 2)
   {
      printf("Usage: %s n\n", argv[0]);
      return -1;
   }
   n = atoi(argv[1]);
   int *a = malloc(n * sizeof(int));
   fill_in_array(a, n);

   printf("Array is created.\n");

   // printf("Original array: \n");
   // print_array(a, n);
   bubble_sort(a, n);

   // printf("Sorted array: \n");
    // print_array(a, n);

   printf("Array is sorted!\n");

   return 0;
}
