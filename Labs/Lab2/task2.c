#include <stdio.h>
int main(){
    int a, b;
    printf("Input: ");
    scanf("%d %d",&a,&b);
    int tempb = b;
    while(tempb > 0){
        printf("*");
        tempb -= 1;
    }
    printf("\n");
    int tempa;
    for(tempa = 2; tempa < a; tempa++){
        printf("*");
        int tempb2 = 2;
        while(tempb2 < b){
            printf(".");
            tempb2 += 1;
        }
        printf("*\n");
    }
    int tempb3 = b;
    while(tempb3 > 0){
        printf("*");
        tempb3 -= 1;
    }
    return 0;
}