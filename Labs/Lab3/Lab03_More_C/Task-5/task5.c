#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int CmpString(const void *p1, const void *p2){
    const char* p1char = *(const char**)p1;
    const char* p2char = *(const char**)p2;
    printf("Comparing %s and %s\n",p1char,p2char);
    return strcmp(p1char,p2char);
}

int main(){
    char *arrStr[] = {"daa", "cbab", "bbbb", "bababa", "ccccc", "aaaa"};
    int arrStrlen = sizeof(arrStr)/sizeof(char *);
    qsort(arrStr,arrStrlen,sizeof(char *),CmpString);
    for(int i = 0; i<arrStrlen; i++) printf("%s ",arrStr[i]);
    return 0;
}
