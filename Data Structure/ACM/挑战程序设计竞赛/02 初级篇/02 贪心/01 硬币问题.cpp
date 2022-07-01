const int V[6] = {1,5,10,50,100,500};

// 输入
int C[6]; // 每种的数目
int A;

void solve(){
    int ans = 0;

    for (int i = 5; i>=0; i--) {
        int t= min(A/V[i], C[i]);  // 使用硬币i的次数
        A -= t*V[i];
        ans += t;
    }
}