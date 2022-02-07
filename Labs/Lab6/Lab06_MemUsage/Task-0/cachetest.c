#include <stdio.h>
#include <stdlib.h>

#define N 64

typedef struct {
  long int v[N];
} StructType;

void SetToZero(StructType* p) {
  int i;
  for(i = 0; i < N; i++)
    p->v[i] = 0;
}

long int GetSum(StructType* p) {
  int i;
  long int sum = 0;
  for(i = 0; i < N; i+=1)
    sum += p->v[i];
  return sum;
}

void ModifyWithStep8(StructType* p, long int a) {
  p->v[0]  += a;
  p->v[8]  += a;
  p->v[16] += a;
  p->v[24] += a;
  p->v[32] += a;
  p->v[40] += a;
  p->v[48] += a;
  p->v[56] += a;
}

void ModifyLow(StructType* p, long int a) {
  p->v[0]  += a;
  p->v[1]  += a;
  p->v[2]  += a;
  p->v[3]  += a;
  p->v[4]  += a;
  p->v[5]  += a;
  p->v[6]  += a;
  p->v[7]  += a;
}

int main() {
  int n = 64;
  StructType* arrOfStructs;
  int nBytesToAllocate = n*sizeof(StructType);
  printf("nBytesToAllocate = %d\n", nBytesToAllocate);
  arrOfStructs = (StructType*)malloc(nBytesToAllocate);
  int m = 1562500;
  long int a;
  a = 1 + (((long int)rand()*3)/RAND_MAX);
  printf("a = %ld\n", a);
  int i, j;
  for(j = 0; j < n; j++)
    SetToZero(&arrOfStructs[j]);
#if 1
  for(i = 0; i < m; i++)
    for(j = 0; j < n; j++)
      ModifyWithStep8(&arrOfStructs[j], a);
#else
  for(i = 0; i < m; i++)
    for(j = 0; j < n; j++)
      ModifyLow(&arrOfStructs[j], a);
#endif
  long int sum = 0;
  for(j = 0; j < n; j++)
    sum += GetSum(&arrOfStructs[j]);
  printf("sum = %ld\n", sum);
  free(arrOfStructs);
  return 0;
}
