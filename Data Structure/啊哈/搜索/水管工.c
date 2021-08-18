#include <stdio.h>
int a[51][51];
int book[51][51];
int n, m, flag = 0;
struct note{
    int x;
    int y;
}s[100];

int top = 0;
void dfs(int x, int y, int front){
    int i;

    //判断是否到达终点
    if(x==n && y==m+1){
        flag = 1; //找到方案
        for(i=1; i<=top; i++)  printf(" (%d, %d) ", s[i].x, s[i].y);
        return;
    }
    //是否越界
    if(x<1 || x>n || y<1 || y>m){
        return;
    }
    //是否在路径中使用过
    if(book[x][y]==1){
        return;
    }

    book[x][y] = 1;

    top++;
    s[top].x = x;
    s[top].y = y;

    //当前是直管
    if(a[x][y]>=5 && a[x][y]<=6){
        if(front==1) //进水口在左边
            dfs(x, y+1, 1);  //使用5
        if(front==2)  //上面
            dfs(x+1, y, 2);   //使用6
        if(front==3)  //右面
            dfs(x, y-1, 3);  //使用5
        if(front==4)   //下边
            dfs(x-1, y, 4);  //使用6
    }

    //当前是弯管
    if(a[x][y]>=1 && a[x][y]<=4){
        if(front==1){//左边
            dfs(x+1, y, 2); //3
            dfs(x-1, y, 4);  //4
        }
        if(front==2){//上边
            dfs(x, y+1, 1); //1
            dfs(x, y-1, 3);  //4
        }
        if(front==3){//右边
            dfs(x+1, y, 2); //1
            dfs(x-1, y, 4);  //2
        }
        if(front==4){//下边
            dfs(x, y+1, 1); //2
            dfs(x, y-1, 3);  //3
        }
    }

    book[x][y] = 0;
    top--;
    return;
}


int main(){
    int i, j, num = 0;
    scanf("%d %d", &n, &m);

    for(i=1; i<=n; i++)
        for(j=1; j<=m; j++)
            scanf("%d",&a[i][j]);
    
    dfs(1,1,1);

    if(flag==0)
        printf("Impossible.\n");

    return 0;
}