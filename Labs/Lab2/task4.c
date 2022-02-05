#include <stdio.h>
#include <stdlib.h>
int main(){
    double a,c,d;
    char b;
    printf("Input: ");
    scanf("%lf%c%lf",&a,&b,&c);
    switch(b) {
        case 43:
        d = a + c;
        break;

        case 45:
        d = a - c;
        break;

        case 42:
        d = a * c;
        break;

        case 47:
        d = a / c;
        break;

        default:
        printf("Invalid operator\n");
        exit(1);
    }
    printf("%lf\n",d);
    return 0;
}