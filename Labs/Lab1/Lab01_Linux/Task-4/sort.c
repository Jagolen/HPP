#include "sort.h"

void bubbleSort(int* arr , int size)

{
  int i,j;
  int tmp;

for (i=0; i<size-1; i++) {
      for (j=0; j<size-1-i; j++)
	if (arr[j+1] < arr[j]) {  /* compare the two neighbors */
	  tmp = arr[j];         /* swap a[j] and a[j+1]      */
	  arr[j] = arr[j+1];
	  arr[j+1] = tmp;
	}
    }

}

void quickSort( int* a, int l, int r)
{
	int j;

	if( l < r ) 
	{
   	// divide and conquer
      j = partition( a, l, r);
	   quickSort( a, l, j-1);
	   quickSort( a, j+1, r);
   }
	
}



int partition( int* a, int l, int r) {
   int pivot, i, j, t;
   pivot = a[l];
	i = l; j = r+1;
		
	while( 1)
	{
		do ++i; while( a[i] <= pivot && i <= r );
		do --j; while( a[j] > pivot );
		if( i >= j ) break;
		t = a[i]; a[i] = a[j]; a[j] = t;
	}
	t = a[l]; a[l] = a[j]; a[j] = t;
   return j;
}
