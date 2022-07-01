// n个顶点，每个顶点染色，使相邻的顶点颜色不同。哦按段能否最多用两种颜色染  

vector<int> G[MAX_V]; // 图
int V; // 顶点数
int color[MAX_V]; // 顶点的颜色（1 or -1）

bool dfs(int v, int c) {
    color[v] = c; // 把顶点v染成c
    for (int i = 0; i < G[v].size(); i++) {
        // 如果相邻的顶点同色则返回false
        if(color[G[v][i]] == c)  return false;
        // 如果没染色则染色成-c
        if(color[G[v][i]] == 0 && !dfs(G[v][i],-c))  return false;
    }

    // 所有顶点都染过色
    return true;
}

void solve() {
    for(int i = 0; i<V; i++) {
        if(color[i]==0) {
            if(!dfs[i, 1]){
                printf("No\n");
            }
        }
    }
    printf("Yes\n");
}