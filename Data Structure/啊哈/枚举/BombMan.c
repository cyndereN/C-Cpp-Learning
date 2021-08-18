#include <stdio.h>

int main(){
    char a[20][21]; // 假设地图大小不超过20*20
    int i, j, sum, map = 0, p, q, x, y, m, n;
    scanf("%d %d", &n, &m);

    for(i=0 ; i<=n-1 ; i++)   scanf("%s", a[i]);

    // 枚举每一个点
    for(i=0 ; i<=n-1 ; i++){
        for(j=0 ; j<=m-1 ;j++){
            if(a[i][j] =='.'){
                sum = 0;
                x = i;
                y = j;
                while(a[x][y] != '#'){
                    if(a[x][y] == 'G')  sum++;
                    x--; //向上统计
                }

                // 向下统计
                x = i;
                y = j;
                while(a[x][y] != '#'){
                    if(a[x][y] == 'G')  sum++;
                    x++; //向下统计
                }

                x = i;
                y = j;
                while(a[x][y] != '#'){
                    if(a[x][y] == 'G')  sum++;
                    y++; //向右统计
                }

                x = i;
                y = j;
                while(a[x][y] != '#'){
                    if(a[x][y] == 'G')  sum++;
                    y--; //向左计
                }

                if(sum>map){
                    map = sum;
                    p = i;
                    q = j;
                }
            }
        }
    }

    printf("将炸弹放置在(%d, %d), 最多可以消灭%d个敌人\n", p, q, map);
    getchar(); getchar();
    return 0;
}