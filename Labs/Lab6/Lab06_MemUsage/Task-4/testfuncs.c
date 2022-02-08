#include "testfuncs.h"
#include <stdio.h>

void transform_std (float * dest, 
		    const float * src, 
		    const float * params, 
		    int n,
		    int np) {
  int i, j;
  int k = 0;
  for (i=0; i<n; i++)
    for(j = 0; j < np; j++) {
      dest[k] = params[j] * src[k] + params[j] * src[k] * src[k];
      k++;
    }
}



void transform_opt (float * restrict dest, 
		    const float * restrict src, 
		    const float * restrict params, 
		    int n,
		    int np) {
  int NP = 2;
  if(np != NP) {
    printf("ERROR: np must be same as NP.\n");
    return;
  }
  int i, j;
  int k = 0;
  for (i=0; i<n; i++)
    for(j = 0; j < NP; j++) {
      dest[k] = params[j] * src[k] + params[j] * src[k] * src[k];
      k++;
    }
}

