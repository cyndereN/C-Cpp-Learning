#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <float.h>
#include "head.h"
#include "stack.h"

void help()
{
    printf("运算符号一览：\n");
    printf("加法:\t+\t减法:\t-\t乘法:\t*\t除法:\t/\n");
    printf("乘方:\t^\t开方:\tsqrt()\t自然对数:ln()\t常用对数:lg()\n");
    printf("正弦:\tsin()\t余弦:\tcos()\t反正弦:\tasin()\t反余弦:\tacos()\n");
    printf("正切:\ttan()\t反正切:\tatan()\tп:\tpi\t自然底数:e\n\n");
    printf("﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌\n");
}
int main()
{
    char c[SIZE_S];
    char cs='\0';//保险
    help();
    do
    {
        printf("键入算式：");
        Scanner(c, SIZE_S);
        system("cls");
        help();
        printf("%s\n", c);
        stack_array n = CreateStack();
        stack_array s = CreateStack();
        Build(c, &s, &n);
        double f=n.Data[0].n;
        printf("=%lf\t", f);
        if(n.Top>1||s.Top>0||f==INFINITY||f==NAN||f!=f)
            printf("栈顶异常，算式可能有误。");
        printf("\n");
    } while (c[0] != '\0');
    system("pause");
    return 0;
}