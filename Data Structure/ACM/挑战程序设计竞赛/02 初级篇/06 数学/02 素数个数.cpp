// O(n^1/2)
bool is_prime(int n){
    for(int i = 2; i*i <= n; i++) {
        if(n%i == 0)  return false; 
    }
    return n != 1;
}

// 埃及筛法O(nloglogn)
int prime[MAX_N]; // 第i个素数
bool is_prime[MAX_N+1]; 

// 返回n以内素数个数
int sieve(int n) {
    int p = 0;
    for (int i=0; i<=n; i++) is_prime[i] = true;
    is_prime[0] = is_prime[1] = false;
    for(int i=2; i<=n; i++) {
        if(is_prime[i] == true) {
            prime[p++] = i;
            for(int j=2*i; j<=n;j+=i)  is_prime[j] = false;
        }
    }
    return p;
}