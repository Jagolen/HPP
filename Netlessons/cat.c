/* cat.c
Copy standard input to standard output.
*/
#include <stdio.h>
int main() {
    char c;
    int i = 0;
    int l = 0;
    c = getchar();
    while(c != EOF) {
        putchar(c);
        c = getchar();
        i = i + 1;
        if(c == '\n') {
            l = l + 1;
        }
    }
    printf("Nr of chars: %d\n", i);
    printf("Nr of lines: %d\n", l);
    return 0;
}