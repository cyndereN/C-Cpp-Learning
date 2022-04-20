/*
有n堆果子，两两合并直到只剩一堆，每次消耗为两堆重量之和，求最小消耗
优先队列维护， Huffman编码
*/
#include <cstdio>
#include <cstdlib>
#include <queue>
using namespace std;
int m, n, i, j, ans;
priority_queue<int,vector<int>,greater<int>> q;

int main(){
    scanf("%d", &n);
    for(i=1 ; i<= n ; i++){
        scanf("%d", &m);
        q.push(m);
    }
    for(i=1;i<n;i++){
        int p1=q.top(); q.pop();
        int p2=q.top(); q.pop();
        ans += p1+p2; q.push(p1+p2);
    }
    printf("%d\n", ans);
    return 0;
}
