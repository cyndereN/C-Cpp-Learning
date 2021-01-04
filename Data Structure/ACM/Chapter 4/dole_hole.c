#include <stdio.h>
#define maxn 25

int n, k, m, a[maxn];

//Anticlockwisely count from p, per t unit. (d=-1: clockwise)
int count(int p, int d, int t){
    while(t--){
        do{ p = (p+d+n-1)%n + 1; } while(a[p] == 0);   //Next number(not 0)
    }
    return p;
}

int main(){
    while(scanf("%d%d%d",&n, &k, &m)==3 && n){
        for(int i=1;i<=n;i++)  a[i] = i;
        int left = n;
        int p1 = n;
        int p2 = 1;
        while(left){
            p1 = count(p1,1,k);
            p2 = count(p2,-1,m);
            printf("%d", p1);  left--;
            if(p2 != p1){
                printf("%3d",p2);  left--;
            }
            a[p1] = a[p2] = 0;
            if(left)  printf(", ");
        }
        printf("\n");
    }
    return 0;
}
