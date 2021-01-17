/* 输入n, 计算s = 1!+2!+3! .... n!的末六位*/

//1
#include <stdio.h>

int main(){
    int n,s = 0;
    scanf("%d",&n);
    if (n>25) n=25;
    for (int i=1;i<=n;i++){
        int factorial = 1;
        for(int j=1;j<=i;j++){
            factorial *= j;
        }
        s += factorial;
    }
    printf("%d\n", s%1000000);
    return 0;
}


//2
#include <stdio.h>
#include <time.h>
int main(){
    const int MOD = 1000000;
    int n, s=0;
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        int factorial = 1;
        for(int j=1;j<=i;j++)
            factorial = (factorial*j%MOD);
        s = (s + factorial) % MOD;
    }
    printf("%d\n",s);
    printf("Time used = %.2f\n", (double)clock()/CLOCKS_PER_SEC); //程序运行时间
    return 0;
}