#include <stdio.h>
int main(){
    double a,b,c,d;
    printf("Input: ");
    scanf("%lf %lf %lf",&a,&b,&c);
    if(a<b) d = b;
    else d = a;
    if(d<c) d = c;
    printf("%lf\n",d);
    return 0;
}