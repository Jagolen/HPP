#include <stdio.h>
#include <math.h>

int main(){
    int a;
    double b;
    printf("Input: ");
    scanf("%d",&a);
    b = (double)sqrt(a);
    if (roundf(b) == b) printf("Perfect square\n");
    else printf("Not perfect square\n");
    return 0;
}