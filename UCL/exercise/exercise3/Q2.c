#include <stdio.h>

int main(void){
    int x, y;
    int a=1, i=0;
    scanf("%d %d",&x, &y);
    printf("%d\n", pow_rec(x,y));
    if (y==0) a=1;
    else{
        a=x;
        while(++i<y){
            a *= x;
        }
    }
    printf("%d",a);
}

int pow_rec(a,b){
    if (b == 0) return 1;
    else{
        return a*pow_rec(a,b-1);
    }
}