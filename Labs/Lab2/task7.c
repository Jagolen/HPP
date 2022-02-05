#include <stdio.h>
int main(){
    int a,reva = 0, rem,b;
    printf("Input: ");
    scanf("%d",&a);
    b = a;
    while(b!=0){
        rem = b%10;
        reva = reva*10+rem;
        b  /= 10;
    }
    if(a == reva) printf("Number is a palindrome\n");
    else printf("Number is not a palindrome\n");
    return 0;
}