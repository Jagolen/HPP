#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[]){
    FILE *data;
    int el;
    double price;
    char *product;
    data = fopen(argv[1],"r");
    fscanf(data,"%d",&el);
    while(fscanf(data,"%s %lf",product,&price) != EOF){
        printf("%s %lf\n",product,price); 
    }
    return 0;
}