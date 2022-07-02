// 我们把对任意1<x<n都有x^n = x mod n 的数称为CarMichael Number
// 加速幂运算
// x^n=((x^2))^2....
// O(logn)
ll mod_pow(ll x,ll n, ll mod) {
    if(n==0) return 1;
    ll res = mod_pow(x*x%mod, n/2, mod);
    if (n&1) res = res*x%mod; // 二进制最低位为1 则乘上x^(2^i)
    return res;
}