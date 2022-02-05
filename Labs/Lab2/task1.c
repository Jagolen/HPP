#include <stdio.h>
int main(){
    int a;
    for(a = 100; a >= 0; a-=4){
        printf("%d\n",a);
    }

    int b = 100;
    while(b >= 0){
        printf("%d\n",b);
        b -= 4;
    }
    return 0;
}