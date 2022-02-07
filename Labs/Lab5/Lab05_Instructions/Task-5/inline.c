static inline int fun(int x){
    return x*x*x*x*x*x*x-x-x-x-x-x-x-x;
}
int main(){
    int x;
    for(int i = 0;i<500000000;i++){
        x = fun(i);
    }
    return 0;
}
