int fact(int n){
    if(n==0) return 1;
    return n*fact(n-1);
}


int fib(int n) {
    if (n<=1) return n;
    return fib(n-1)+fib(n-2);
}

int memo[MAX_N+1];
int fib(int n) {
    if(n<=1)  return n;
    if(memo[n] != 0)  return memo[n];
    return memo[n] = fib(n-1) + fib(n-2);
}