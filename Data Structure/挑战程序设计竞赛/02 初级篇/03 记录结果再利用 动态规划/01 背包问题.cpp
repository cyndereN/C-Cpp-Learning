// n个重量和价值为wi, vi的物品，挑选出总重量不超过W的，求价值总和的最大值

// 普通穷竭搜索 O(2^n)
int n, W;
int w[MAX_N], v[MAX_N];
// 从第i个物品开始挑选总重小于j的部分时，总价值的最大值
int rec(int i, int j) {
    int res;
    if (i==n) {
        // 已经没有剩余物品了
        res = 0;
    } else if (j<w[i]) {
        // 无法选择这个物品
        res = rec(i+1, j);
    } else {
        // 挑选和不挑选都尝试一下
        res = max(rec(i+1, j), rec(i+1, j-w[i])+v[i]);
    }
    return res;
}

rec(n,W);

// 动态规划

int dp[MAX_N+1][MAX_W+1];

void solve() {
    for(int i=n-1; i>=0; i--) {
        for(int j=0; j<= W; j++){
            if (j<w[i])
                dp[i][j] = dp[i+1][j];
            else
                dp[i][j] = max(dp[i+1][j],dp[i+1][j-w[i]]+v[i]);
        }
    }

    printf("%d\n", dp[0][W]);
}

// 完全背包问题，每件单品数量无限制

int dp[MAX_W+1];
void solve(){
    for(int i = 0; i<n; i++){
        for (int j = 0; j<=W;j++){
            if(j<w[i]) {
                dp[i+1][j] = dp[i][j];
            } else {
                dp[i+1][j] = max(dp[i][j], dp[i+1][j-w[i]] +v[i]);
            }
        }
    }
}