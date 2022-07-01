// dp[i][j]= s1...si 和 t1...tj对应的LCS长度
// s1...s(i+1)和t1...t(j+1)对应的公共子列可能是
// 当s(i+1)=t(j+1), 在s1...si 和 t1...tj的公共子列末尾追加上s(i+1)
// s1...si 和 t1...t(j+1)的公共子序列
// s1...s(i+1) 和 t1...tj的公共子序列
// 中的一个

// O(nm)
int n,m;
char s[MAX_N], t[MAX_M];
int dp[MAX_N+1][MAX_M+1];

void solve(){
    for(int i = 0; i<n; i++) {
        for(int j = 0; j<m; j++){
            if(s[i]==s[j]){
                dp[i+1][j+1]=d[i][j]+1;
            }
            else {
                dp[i+1][j+1] = max(d[i][j+1], dp[i+1][j]);
            }
        }
    }
}

//初始化记忆数组
memset(dp, 0, sizeof(dp));