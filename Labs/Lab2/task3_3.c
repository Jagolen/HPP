#include <stdio.h>
#include <math.h>
int main(){
    double a,b,c,d,temp;
    printf("Input: ");
    scanf("%lf %lf %lf",&a,&b,&c);
    if((fabs(a) < fabs(b) && fabs(a) > fabs(c)) || (fabs(a) < fabs(c) && fabs(a) > fabs(b))) d = a;
    else if((fabs(b) < fabs(a) && fabs(b) > fabs(c)) || (fabs(b) < fabs(c) && fabs(b) > fabs(a))) d = b;
    else d = c;
    printf("%lf",d);
    return 0;
}