/* factorial.c
Program that tabulates the factioral function
*/
#include <stdio.h>

int factorial(int n) {
    if(n==0) {
        return 1;
    } else if (n<0) {
        printf("Error");
    } else {
        return n*factorial(n-1);
    }
}

int main() {
    int i = -1;
    while(i <= 10) {
        printf ("%2d %15d \n", i, factorial(i));
        i = i + 1;
    }
    return 0;
}