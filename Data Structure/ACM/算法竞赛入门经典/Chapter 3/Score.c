/*
OOXXOXXOOO 1+2+0+0+1+0+0+1+2+3
*/


#include <stdio.h>
#include <string.h>
#define maxn 105

int main(void){
    int T;
    scanf("%d",&T);

    while(T--){
        char s[maxn];
        scanf("%s", s);
        int sum = 0, n = strlen(s);
        for(int i=0;i<n;i++){
            int a=0, d=1;
            if(s[i]=='O'){
                a = 1;
                for(;i<n-1;i++){
                    if(s[i+1]!='O')  break;
                    d += 1;
                    a += d;
                }
            }
            sum += a;
        }
        printf("%d\n", sum);
    }

    return 0;
}