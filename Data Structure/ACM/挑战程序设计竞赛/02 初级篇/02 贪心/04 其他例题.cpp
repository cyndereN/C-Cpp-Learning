// POJ3069 Saruman's Army
// 一条直线有N个点，选择若干个加上标记，要求每个点距离为R以内的区域里必须带有标记的点

// 从最左边开始考虑，对于这个点到距其R以内的区域内必须要有带有标记的点。下一个点也如此，不断重复

int N, R;
int X[MAX_N];

void solve() {
    sort(X, X+N);

    int i = 0, ans = 0;

    while (i<N) {
        // s是没有被覆盖的最左的点的位置
        int s = X[i++];
        // 一直向右前进直到距S的距离大于R的点
        while(i<N && X[i] <= s+R)  i++;

        // p是新加上标记的店的位置
        int p = X[i-1];

        // 一直向右前进直到距p的距离大于R的点
        while(i<N && X[i] <= p+R) i++;
        ans++;
    }
}


// POJ3253 Fence Repair
// 将一块很长的木板切割成N块。准备切成的木板为L1~Ln。
// 每次切断木板时需要的开销为这块木板的长度
// 求最小开销

//e.g. 输入 N=3, L= {8, 5, 8}
// 输出 34 (34 = 21 + 13)

// 利用二叉树,开销的合计是各叶子结点的木板长度*节点的深度之和
// 最短的板和次短的板的节点应当是深度最大的兄弟节点

typedef long long ll;
int N, L[MAX_N];

void solve() {
    ll ans = 0;

    // 直到计算到木板为1块时为止
    while (N>1) {
        // 求出最短的板子mii1和次短的mii2
        int mii1 = 0, mii2 = 1;
        if(L[mii1] > L[mii2]) swap(mii1, mii2);
        for(int i = 2; i<N; i++) {
            if(L[i] < L[mii1]) {
                mii2 = mii1;
                mii1 = i;
            }
            else if (L[i] < L[mii2]) {
                mii2 = i;
            }
        }

        // 拼合
        int t = L[mii1] + L[mii2];
        ans+=t;

        // 将最短的与次短的更新，一个是t，一个是遍历的最后一个数（L[N-1]）
        if(mii1 == N-1)  swap(mii1, mii2);  
        L[mii1] = t;
        L[mii2] = L[N-1];
        N--;
    }
}