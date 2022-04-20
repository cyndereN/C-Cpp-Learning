#include <stdio.h>

int main(void){
    int n, m;
    scanf("%d", &n);
    m = (n%10)*100 + (n/10%10)*10 + n/100;
    printf("%03d\n", m);
}