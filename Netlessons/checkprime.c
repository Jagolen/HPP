#include <stdio.h>
#include <math.h>
#include <stdbool.h>

bool isprime(int n) {
    for(int i=2; i<=sqrt(n);i++) {
        if (n%i == 0) {
            return false;
        }
    }
    return true;
}

int main() {
    for(int n = 2; n<=15; n++) {
        printf("%d is prime: %d\n",n,isprime(n));
    }
    return 0;
}