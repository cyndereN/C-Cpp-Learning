// N*M大小的园子，雨后激起了水。求多少水洼
// ***
// *W*
// ***

// 从任一w开始，利用DFS不停把邻接部分用'.'代替，直到图中不再存在W为止
// DFS的次数就是答案

int N, M;
char field[MAX_N][MAX_M+1]; //园子

// 现在位置x,y
void dfs(int x, int y) {
    // 现在位置替换为.
    field[x][y] = '.';

    // 循环遍历8个方向
    for(int dx=-1; dx<=1; dx++){
        for(int dy=-1; dy<=1; dy++){
            int nx = x+dx, ny = y+dy;

            // 判断(nx, ny)是不是在园子内，以及是否有积水
            if(0<=nx && nx<N && 0<=ny && ny<M && field[nx][ny] == "W")  dfs(nx, ny);
        }
    }

    return;
}

void solve() {
    int res = 0;

    for(int i=0; i<N ; i++){
        for(int j=0; j<M ; j++){
            if(field[i][j]=="W"){
                dfs(i, j);
                res++;
            }
        }
    }
    printf("%d", res);
}