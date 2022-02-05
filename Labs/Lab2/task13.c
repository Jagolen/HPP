#include <stdio.h>

int main(){
    FILE *data;
    int el;
    double price;
    char *product;
    data = fopen("data.txt","r");
    fscanf(data,"%d",&el);
    while(fscanf(data,"%s %lf",product,&price) != EOF){
        printf("%s %lf\n",product,price); 
    }
    return 0;
}