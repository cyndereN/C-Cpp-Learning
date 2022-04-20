//Sum of the elements
int sum(int* a, int n){
    int ans = 0;
    for(int i=0;i<n;i++)
        ans += a[i];
    return ans;
}

//Sum of [begin, end]
int sum(int* begin, int* end){
    int ans = 0;
    for(int *p = begin;p!=end;p++){
        ans += *p;
    }
    return ans;
}

//factorial
int f(int n){
    return n == 0 ? 1 : n*f(n-1)
 }