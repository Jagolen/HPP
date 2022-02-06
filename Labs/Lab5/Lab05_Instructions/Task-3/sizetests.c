#include <math.h>
#include <stdio.h>
int main(){
    float largea = 1, smalla = 1;
    double largeb = 1, smallb = 1;
    for(int i = 1; i<310; i++){
        (float)(largea *= 10);
        (float)(smalla /= 10);
        (double)(largeb *= 10);
        (double)(smallb /= 10);
        printf("larger float = %f\n",largea);
        printf("smaller float = %.30f\n",smalla);
        printf("larger double = %lf\n",largeb);
        printf("smaller double = %.30lf\n",smallb);
    }
    double notnumber = sqrt(-1);
    printf("%lf\n", notnumber);
    notnumber++;
    printf("%lf\n", notnumber);
    double eps = 1;
    while(eps+1 != 1){
        eps *= 0.5;
    }
    printf("%.20lf\n",eps);



    return 0;
}