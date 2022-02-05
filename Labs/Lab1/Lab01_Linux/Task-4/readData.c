#include "readData.h" 

int* readData( int* arr , int size) 
     
/* Prompt user for file */ 
{ 
  FILE *fopen(), *fp; 
  int c, nc, nlines; 
  char * p;
  char d;
  char filename[40];
  char buff[4]; 
  int i = 0;
  int j =0;
  int k;
  nlines = 0 ;
  nc=0;
  
  printf("Enter file name: "); 
  fgets(filename, sizeof(filename), stdin);
  
  // find and remove the trailing newline character
  if ((p = strchr(filename, '\n')) != NULL)
      *p = '\0';

  fp = fopen( filename, "r" );      
  if ( fp == NULL )  
  { 
      printf("Cannot open %s for reading \n", filename ); 
      exit(1);      /* terminate program */ 
  }  
    
  arr = allocateMemory(arr , size);
  
  d = getc( fp ) ;
  
  while (  d != EOF )
  { 
     if ( d  ==  '\n' )   
	 {  
	  	nlines++ ;
	  	arr[j] = atoi(buff);
	  	i = 0;
	 	j++;
	 	if(j == size)
	    	break;
	  	for(k=0 ; k< 4 ; k++ )
	    	buff[k] = NULL;
	 }
     if(i < 4)
		buff[i++] = d;
		
      nc++ ;  
      d = getc ( fp ); 
  }  
  fclose( fp );
  
  if ( nc != 0 )      
     printf("\n %d numbers reads from the file \n", nlines );
  else     
     printf("File: %s is empty \n", filename ); 
  
    return (arr);
}  

int* allocateMemory(int* arr, int size)
     
{
  arr = (int*) malloc(size*sizeof(int));
  
  return(arr);
}

