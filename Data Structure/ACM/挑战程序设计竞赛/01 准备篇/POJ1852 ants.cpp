// 在一根长为L的水平木棍上有一群数量为n的蚂蚁，它们以每秒1cm/s的速度走到木棍一端就会掉下去。
// 现在知道它们的起始位置是距离木根左端点的x处。但是不知道它们爬行的方向。在相向而行的两只蚂
// 蚁相遇后，它们会掉头往反方向走。问所有蚂蚁都落下木棍的最快时间和最慢时间。

int L, n;
int x[MAX_N];

void solve(){
    // 计算最短时间
    int minT = 0;
    for (int i = 0; i<n; i++) {
        minT = max(minT, min(x[i], L-x[i]));
    }

    int maxT = 0;
    for (int i = 0; i<n; i++) {
        maxT = max(maxT, max(x[i], L-x[i]));
    }
}