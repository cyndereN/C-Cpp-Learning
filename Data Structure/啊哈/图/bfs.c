#include <stdio.h>
const int INF = 0x3f3f3f3f;
int main(){
    int i, j, n, m, a, b, cur;
    int book[101] = {0} 
    int e[101][101];
    int que[10001], head, tail;
    scanf("%d %d", &n, &m);

    //初始化二维矩阵
    for(i=1; i<=n; i++)
        for(j=1; j<=n; j++)
            if(i==j) e[i][j]=0;
            else e[i][j]=INF;

    //读入顶点间的边
    for(i=1; i<=m; i++){
        scanf("%d %d", &a, &b);
        e[a][b] = 1;
        e[b][a] = 1;
    }
    
    head = 1;
    tail = 1;

    //从1号顶点出发，将1号顶点加入队列
    que[tail] = 1;
    tail ++;
    book[1] = 1; //将一号顶点标为已访问

    //当队列不为空时循环
    while(head<tail && tail<=n){
        cur = que[head]; //当前正在访问的顶点编号
        for(i=1; i<=n; i++){ // 从1~n依次尝试
            //判断从顶点cur到顶点i有边，且i未访问，将i入队
            if(e[cur][i] == 1 && book[i] == 0){
                que[tail] = i;
                tail++;
                book[i] = 1;
            }
            // 如果tail大于n，证明所有顶点已经被访问过
            if(tail>n) break;
        }
        head++; 向下扩展
    }
    for(i=1; i<tail; i++)   
        printf("%d ", que[i]);
    
    return 0;
}