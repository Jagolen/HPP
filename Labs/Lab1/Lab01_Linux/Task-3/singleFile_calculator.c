#include<stdio.h>

int add(int num1 , int num2)
    {
        return (num1+num2);
    }
int subtract(int num1 , int num2)
    {
        return (num1-num2);
    }


int main(){

    int num1 = 50;
    int num2 = 50;

    printf("\n result of adding %d and %d is %d",num1,num2,add(num1,num2));
    printf("\n result of subtracting %d and %d is %d\n",num1,num2,subtract(num1,num2)); 

}



