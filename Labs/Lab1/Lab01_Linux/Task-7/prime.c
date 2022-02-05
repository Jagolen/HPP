#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#define NDEBUG
int is_prime(int n);

int main(){
    
    int n, nprime;
    int *prime;
    
    printf("Give a number: ");
    scanf("%d", &n);
    prime=(int *)malloc(n*sizeof(int));
  
    
    // Compute all primes
    prime[0]=2;nprime=1;
    for (int number=2;number<=n;number+=2){
        if (is_prime(number)){
            prime[nprime]=number;
            nprime++;
        }
    }
    
    if (nprime<1000){
        for (int i=0;i<nprime;i++){
            printf("%d\n",prime[i]);
	}
    printf("Total number of primes: %d\n",nprime);
    return 0;
    }
}


int is_prime(int n){
    for (int i=2;i<=sqrt(n);i++){
        if (n%i==0){
            return 0;
        }
    }
    return 1;
}
