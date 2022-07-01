// 只需要从板的集合里取出最短的两块，并把长度为凉快不拿长度之和的板加入其中即可
// O(nlogn)

typedef long long ll;

// 输入
int N, L[MAX_N];

void solve(){
    ll ans = 0;

    priority_queue<int, vector<int>, greater<int>> que;

    for (int i = 0; i<N; i++)
        que.push(L[i]);
    
    // 循环到只剩一个木板为止
    while (que.size() > 1){
        int l1, l2;
        l1 = que.top();
        que.pop();
        l2 = que.top();
        que.pop();

        ans += l1+l2;
        que.push(l1+l2);
    }
}