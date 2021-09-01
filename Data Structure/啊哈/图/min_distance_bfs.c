#include <stdio.h>
#define INF 99999999
int min = INF, book[101], n, e[101][101];

// cur: 当前编号, dis: 已经走过的路程
void dfs(int cur, int dis){
    int j; // 如果当前走过的路程已经大于之前找到的最短路
    if(dis>min)  return;
    if(cur == n) {//到达
        if(dis<min)  min = dis; 
        return;
    } 

    for(j=1; j<=n; j++){
        //判断是否有路,是否在走过的路径中
        if(e[cur][j] != INF && book[j]==0){
            book[j]=1; //标记j已经在路径中
            dfs(j, dis+e[cur][j]); //从城市J出发寻找目标城市
            book[j]=0;
        }
    }
    return;
}

int main(){
    int i,j,m,a,b,c;
 	scanf("%d %d",&n,&m);
 	for(i=1;i<=n;i++)  //初始化二维矩阵
	 	for(j=1;j<=n;j++)
		 	if(i == j) e[i][j]=0;
			else e[i][j]=INF;
			 
	for(i=1;i<=m;i++)
	{
		scanf("%d %d %d",&a,&b,&c);
		e[a][b] = c;
	} 
	 
	//从1号城市出发
	book[1]=1;  //标记1号城市已经在路径中
	dfs(1,0);  //1表示当前所在的城市编号，0表示当前已经走过的路程
	printf("%d",min);  //打印1号城市到5号城市的最短路径
	
	return 0; 
}