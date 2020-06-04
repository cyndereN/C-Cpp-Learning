#include<stdio.h>
void main()
{
    int result; 									/*定义无符号变量*/
    int a, b;
    printf("please input a:");
    scanf("%d",&a);
    printf("please input b:");
    scanf("%d",&b);
    printf("a=%d,b=%d", a, b);
    result = a|b;										/*计算或运算的结果*/
    printf("\na|b=%c\n", result);
}
