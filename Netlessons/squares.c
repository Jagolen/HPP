/* squares.c
Program that writes a table over squares
of the numbers 1, 2, ... 10
*/
#include <stdio.h>
int main(){
    int i = 1;
    while( i<=10 ) {
        printf( "%d \t %d \n", i, i*i);
        i = i + 1;
    }
    return 0;
}