//第一行个数，第二行数据，输入0结束
#include <stdio.h>
#define INF 1000000000

int main(){
    int x, n = 0, kase = 0;
    while(scanf("%d",&n)==1 && n){
        int s=0, max = -INF, min = INF;
        for(int i=0; i<n ; i++){
            scanf("%d", &x);
            s+= x;
            if(x<min) min = x;
            if(x>max) max = x;
        }
        if (kase) printf("\n");
        printf("Case %d: %d %d %.3f", ++kase, min, max, (double)s/n);
    }
    return 0;
}