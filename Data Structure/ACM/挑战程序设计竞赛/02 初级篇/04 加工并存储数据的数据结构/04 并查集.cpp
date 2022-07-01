// 并查集是一种用来管理元素分组情况的数据结构
// 可以高效进行如下操作
// 1. 查询a与b是否属于同一组
// 2. 合并a与b所在的组


// 类似一个森林，每一组是一棵树

// 1.查询：沿着树向上走，如果根一样则同组。路径压缩：查询过程中向上经过的结点都改为直接连到根上。O(a(n)) a(n)是阿克曼函数的反函数不小于O(logn)
// 2.合并：从一个组的根向另一组的根连线。从rank(高度)小的向大的连边

int rank[MAX_N];
int par[MAX_N];

void init(int n){
    for(int i = 0; i<n; i++){
        par[i] = i;
        rank[i] = 0;
    }
}

int find(int x) {
    if (par[x] == x) {
        return x;
    } else {
        return par[x] = find(par[x]); // 递归
    }
}

void unite(int x, int y) {
    x = find[x];
    y = find[y];

    if (x == y)  return;
    if(rank[x]<rank[y]) {
        par[x] = y;
    } else {
        par[y] = x;
        if(rank[x]==rank[y])  rank[x]++;
    }
}