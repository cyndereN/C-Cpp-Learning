#include <stdio.h>

int main()
{
    int a, b, c, cnt = 1;
    while(3 == scanf("%d%d%d", &a, &b, &c)){
        if(0 == a && 0 == b && 0 == c) break;
        int integer = a / b;                        // 获得整数部分
        printf("Case %d: %d.", cnt++, integer);
        a %= b; // 获得余数
        int i = 1;
        // 进行c-1次模数学拟除法求出小数点后c-1位,因为要四舍五入,所以最后一位单独处理
        while(i++ < c){
            a *= 10;
            printf("%d", a / b);
            a %= b;
        }
        a *= 10;
        // 判断最后一位的下一位是否大于5,进行四舍五入
        printf("%d\n", ((a % b) * 10 / b > 5) ? (a / b + 1) : (a / b));
    }
    return 0;
}