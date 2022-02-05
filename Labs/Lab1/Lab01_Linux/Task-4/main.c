#include "main.h"

int main()

{
  int* arr; 
  int size = 10;
  
  int i;
  arr = readData(arr,size);
  printf("\n Unsorted data ...");
  printArray(arr ,size);  
  bubbleSort(arr , size);
  printf("\n Sorted Data ...");
  printArray(arr , size);
  printf("\n");
   
  return(0);

}

void printArray(int* arr, int size)
{
  int i;
for (i=0 ; i<size ; i++)
    printf("\n arr[%d] = %d  ",i,arr[i]);

}




