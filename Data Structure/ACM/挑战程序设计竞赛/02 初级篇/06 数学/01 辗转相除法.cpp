// O(log(max(a,b)))

int gcd(int a, int b) {
    if(b==0) return a;
    return gcd(b, a%b);
}

// 求整数x,y使ax+by=1
int extgcd(int a, int b, int& x, int& y){
    int d=a;
    if(b!=0) {
        d=extgcd(b,a%b, y, x);
        y -= (a/b) * x;
    } else {
        x = 1; y = 0;
    }
    return d;
}