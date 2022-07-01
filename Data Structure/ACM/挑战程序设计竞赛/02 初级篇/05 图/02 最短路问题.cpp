// 1. Bellman-Ford O(EV)
// 一般方法，能解决有负权边的dag，但是无法解决负圈
struct edge{int from, to, cost;};
edge es[MAX_E];
int d[MAX_V];
int V, E;

// 求顶点s出发到所有点的最短距离
void shortest_path(int s) {
    for(int i = 0; i<V; i++)  d[i] = INF;
    d[s] = 0;

    while(true) {
        bool update = false;
        for (int i = 0;i <E; i++) {
            edge e = es[i];
            if(d[e.from] != INF && d[e.to] > d[e.from] + e.cost){
                d[e.to] = d[e.from] + e.cost;
                update = true;
            } 
        }
        if (!update)  break;
    }
}


// 判断负圈(最短路不会通过同一个顶点两次)
bool find_nega_loop(){
    memset(d, 0, sizeof(d));

    for(int i = 0; i< V; i++){
        for(int j = 0; i<E; j++){
            edge e = es[j];
            if(d[e.to] > d[e.from] + e.cost) {
                d[e.to] = d[e.from] + e.cost;
                // 如果第V次仍然更新了，则存在负圈
                if(i==V-1)  return true;
            }
        }
    }
}

// 2. Dijkstra O(V^2) 优化后O(ElogV)
int cost[MAX_V][MAX_V] // cost[u][v]表示e=(u,v)的权值
int d[MAX_V];
bool used[MAX_V];
int prev[MAX_V];

int V;
// 起点s到各个顶点的最短距离
void dijkstra(int s){
    fill(d, d+V, INF);
    fill(used, used+V, false);
    // fill (prev, prev+V, -1);
    d[s] = 0;

    while(true) {
        int v= -1;
        // 从尚未使用过的顶点中选择一个距离最小的
        for(int u = 0; u<V; u++) {
            if(!used[u] && (v==-1 || d[u]<d[v]))  v= u;
        }
        if (v==-1)  break;
        used[v] = true;

        for(int u = 0; u<V; u++) {
            d[u] = min(d[u], d[v]+cost[v][u]);
            // prev[u]=v;
        }
    }
}

// 路径还原
vector<int> get_path(int t) {
    vector<int> path;
    for(; t!=-1; t= prev[t])  path.push_back(t); // 不断沿着prev[t]走直到t=s
    reverse(path.begin(), path.end());
    return path;
}

// 堆优化
struct edge{int from, to, cost;};

typedef pair<int, int> P; // first 是最短距离，second是顶点的编号

void dijkistra(int s) {
    // 通过指定greater<P>参数，堆按照first从小到大的顺序取出值
    priority_queue<P, vector<P>, greater<p>> que;
    fill(d, d+V, INF);
    d[s] = 0;
    que.push(P(0, s));

    while(!que.empty()) {
        P p = que.top(); que.pop();
        int v = p.second;
        if (d[v] < p.first)  continue;

        for(int i=0; i<G[v].size(); i++){
            edge e = G[v][i];
            if(d[e.to] > d[v] + e.cost) {
                d[e.to] = d[v] + e.cost;
                que.push(P(d[e.to], e.to));
            }
        }
    }
}

// 3. Floyd-Warshall
int d[MAX_V][MAX_V];
int V;

void floyd_warshall(){
    for(int k=0; k<V; k++)
        for(int i=0; i<V; i++)
            for(int j=0; j<V; j++)
                d[i][j] = min(d[i][j], d[j][k]+d[k][j]);
}