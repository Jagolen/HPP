#include <stdio.h>
void print_int_1(int x){
    printf("Here is the number: %d\n",x);
}
void print_int_2(int x){
    printf("Wow, %d is really an impressive number!\n",x);
}
int main(){
    int x;
    void (*funpoint)(int);
    printf("Input: ");
    scanf("%d",&x);
    funpoint = &print_int_1;
    funpoint(x);
    funpoint = &print_int_2;
    funpoint(x);
    return 0;
}