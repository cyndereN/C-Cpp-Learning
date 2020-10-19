#include <stdio.h>
#include <stdlib.h>

int main(void){
    int a,b,d;
    scanf("%d %d", &a, &b);
    if (a>b) printf("%d\n", product(a,b));
    else printf("%d\n", product(b,a));
    return 0;
}

int product(x,y){
    int p = x, s = 1;
    do{
        s *= p;
    }while(p-->y);
    return s;
}