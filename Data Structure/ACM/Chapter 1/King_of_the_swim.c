#include <stdio.h>

const double eps = 1e-8;
int main(){
    double b, ans = 0;
    double temp = 2;
    scanf("%lf", &b);
    int i;
    for(i=0; b-ans>eps; i++){
        ans += temp;
        temp *= 0.98;
    }
    printf("%d\n", i);
    return 0;
}