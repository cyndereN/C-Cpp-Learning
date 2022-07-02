// Prim算法
// 和Dijkstra相似。从某个顶点出发不断添加边
// 首先假设一棵只包含一个顶点V的树T。然后贪心地选取T和其他顶点之间相连的最小权值的边
// 并加入T，不断进行这个操作就可以得到一棵生成树了

int cost[MAX_V][MAX_V];
int mincost[MAX_V];
bool used[MAX_V];
int V;

int Prim(){
    for (int i = 0; i<V; i++) {
        mincost[i] = INF;
        used[i] = false;
    }
    mincost[0] = 0;
    int res = 0;

    while (true) {
        int v = -1;
        // 从不属于X的顶点中选取从X到其权值最小的顶点
        for(int u = 0; u<V; u++) {
            if(!used[u] && (v==-1 || mincost[u] < mincost[v])) v=u; 
        }
        if (v==-1) break;
        used[v] = true;
        res+= mincost[v];
        for(int u=0; u<V; u++){
            mincost[u] = min(mincost[u], cost[v][u]);
        }
    }

    return res;
}

// Kruskal算法
// 和bellman-frod类似，按照边的权值从小到大查看一遍，如果不产生圈就加到生成树中
struct edge {int u, v, cost; };
bool comp(const edge& el, const edge& e2) {
    return e1.cost < e2.cost;
}

edge es[MAX_E];
int V, E;

int Kruskal(){
    sort(es, es+E, comp);
    init_union_find(V);
    int res = 0;
    for(int i = 0; i< E;i++) {
        edge e = es[i];
        if(!same[e.u, e.v]){
            unite(e.u, e.v);
            res+= e.cost;
        }
    }
}