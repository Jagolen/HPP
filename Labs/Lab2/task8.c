#include <stdio.h>
int main(){
    int a = 2;
    char b = 'b';
    double c = 3.14;
    printf("%d %c %lf\n",a,b,c);
    printf("%p %p %p\n",&a,&b,&c);
    printf("%ld %ld %ld\n",sizeof(a),sizeof(b),sizeof(c));
}