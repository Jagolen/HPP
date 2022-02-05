#include <stdlib.h>
#include <stdio.h>

int main(){
    int a = 1, input = 1,counter = 0,tens = 0,move = 0, tenval[10], sum = 0;
    int* out;
    printf("Input: ");
    while(input !=0){
        input = scanf("%1d",&a);
        tenval[tens] = a;
        sum += a;
        counter += 1;
        tens += 1;
        if(tens == 9){
            if(move == 0){
                out = (int*)malloc(10*sizeof(int));
            }
            else{
                out = realloc(out,(move+10)*sizeof(int));
            }
            for(int i = 0; i < 10; i++){
                out[i+move] = tenval[i];
            }
            tens = 0;
            move += 10;
        }
    }
    out = realloc(out,(move+tens)*sizeof(int));
    for(int n = 0; n<=tens; n++){
        out[n+move] = tenval[n];
    }
    printf("Output: ");
    for(int m = 0; m<counter; m++){
        printf("%d ",out[m]);
    }
    printf("\nSum: %d\n",sum);
}