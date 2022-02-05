/*
sum.c
Reads and sums positive numbers.
Ends when a non positive number is read.
*/

#include <stdio.h>

int main() {
    double sum = 0;
    int n;
    float x;
    scanf("%f",&x);
    while(x>0) {
        n++;
        sum += x;
        scanf("%f",&x);
    }
    printf("Numbers read : %3d\n", n);
    printf("Sum of numbers: %5.2f\n", sum);
}