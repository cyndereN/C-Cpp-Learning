// 部分和问题
// 给定整数a1, a2, ... an, 判断是否可以选出若干数使和恰好为k

int a[MAX_N];
int n, k;

// 已经从前i项得到了和sum，然后对于i项之后进行分支
bool dfs(int i, int sum) {
    // 前n项计算过，返回是否与k相等
    if (i==n)   return sum == k;

    // 不加上a[i]的情况
    if (dfs(i+1, sum))  return true;

    // 加上a[i]
    if (dfs(i+1, sum+a[i]))  return true;

    // 无论是否加上a[i]都不能凑成k就返回false
    return false;
}
void solve(){
    if(dfs(0,0))  printf("yes");
    else printf("no");
}