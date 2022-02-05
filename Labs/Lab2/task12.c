#include <stdio.h>
#include <stdlib.h>



int main(){
    int a;
    printf("Input: ");
    scanf("%d",&a);
    int *p = (int*)malloc(a*sizeof(int));
    for(int i=1;i<a;i++) p[i] = i+1;
}