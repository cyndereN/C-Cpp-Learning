#include <stdio.h>

int main(void){
    int n2, count = 0;
    scanf("%d",&n2);//-2^31~2^31-1 
    long long n = n2; //-2^63~2^63-1
    while (n>1){
        if(n%2==1) n=3*n+1;
        else n/=2;
        count++;
    }
    printf("%d\n",count);
    return 0;
}