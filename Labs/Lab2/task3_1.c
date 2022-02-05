#include <stdio.h>
int main(){
    int a,b,c;
    printf("Input: ");
    scanf("%d %d",&a,&b);
    if(a%2 == 0 && b%2 == 0){
        c = a + b;
    }
    else{
        c = a * b;
    }
    printf("%d\n",c);
    return 0;
}