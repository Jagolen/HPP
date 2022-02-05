#include<stdio.h>

float arr[100];
int size=100;

int main()
{
    int i;
    float sum = 0.0;
    arr[0] = 1;
    for(i=1; i<size; i++)
    {
        arr[i] = 0.5*arr[i-1];
        sum += arr[i];
    }
    printf("Welcome to the first Lab of the HPP course!\n");
    printf("sum = %f\n",sum);
}
