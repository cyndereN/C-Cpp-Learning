#include <stdio.h>
#include <string.h>
#define maxn 20
int a[maxn][maxn];

int main(){
    int n, x, y, tot=0;
    scanf("%d", &n);
    memset(a, 0, sizeof(a));  //Quicker
    tot = a[x=0][y=n-1] = 1; //Assign values to both x, y, a[0][n-1] and tot

    while(tot < n*n){
        while(x+1<n && !a[x+1][y]) a[++x][y] = ++tot;
        while(y>0 && !a[x][y-1]) a[x][--y] = ++tot;
        while(x>0 && !a[x-1][y]) a[--x][y] = ++tot;
        while(!a[x][y+1]) a[x][++y] = ++tot;
    }

    for (x=0;x<n;x++){
        for(y=0;y<n;y++) printf("%4d", a[x][y]);
        printf("\n");
    }
    return 0;
}