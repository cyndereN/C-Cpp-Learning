// dp[i] = 以ai为末尾的最长上升子序列的长度

// 是只包含ai的子序列
// 在满足j<i并且aj<ai的以aj为结尾的上升子列末尾，追加上ai后得到的子序列

// O(n^2)
int n;
int a[MAX_N];

int dp[MAX_N];

void solve() {
    int res = 0;
    for(int i = 0; i < n; i++) {
        for (int j=0; j<i ;j++){
            if (a[j]<a[i]){
                dp[i] = max(dp[i], dp[j+1]);
            }
        }
        res = max(res,dp[i]);
    }

}