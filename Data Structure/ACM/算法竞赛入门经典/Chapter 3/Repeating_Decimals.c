/*
a=5, b=43, a/b=0.(11627.....456)
*/

#include <stdio.h>
#include <string.h>
#define maxn 3005

int main(){
    int a, b, cnt=0;
    scanf("%d %d",&a,&b);
    int integer = a/b;
    int rem[maxn];
    int dec[maxn];

    rem[0] = a - integer * b;

    for(int i=0;i<maxn;i++){
        rem[i+1]=10*rem[i];
        if(rem[i+1]<b) dec[i]=0;
        else{
            dec[i] = rem[i+1]/b;
            rem[i+1] -= b*dec[i];
        }

        cnt++;

        if (rem[i+1]==0 || rem[i+1]==rem[0])  break;
    }

    printf("%d.(", integer);
    for(int i=0;i<cnt;i++) printf("%d", dec[i]);
    printf(")\n");

    return 0;
}