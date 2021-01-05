/*
x = 100a + 10b + c
if x + a + b + c = y, we say x is digit generator of y.
e.g. for n = 216, 121, 2005, solutions are 198, 0, 1979 (0 means no solution)
*/

#include <stdio.h>
#include <string.h>
#define maxn 100005

int ans[maxn];

int main(){
    int T, n;
    memset(ans, 0, sizeof(ans));
    for(int m = 1; m < maxn; m++){
        int x = m, y = m;
        while (x>0)  { y += x%10; x /= 10; }
        if(ans[y]==0||m<ans[y]) ans[y] = m;
    }
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &n);
        printf("%d\n", ans[n]);
    }
    return 0;
}