#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "stack.h"
#include <corecrt_math_defines.h> //vs2019编译还需要引用这个头文件
#define LEN 8

int InLevel(char s[]) //运算优先级，可以发现括号的优先级特别高
{
    if (strcmp(s, "(") == 0)
        return 2147483647;
    if (strcmp(s, "+") == 0 || strcmp(s, "-") == 0)
        return 0;
    if (strcmp(s, "*") == 0 || strcmp(s, "/") == 0)
        return 1;
    if (strcmp(s, "^") == 0 || strcmp(s, "sqrt ") == 0)
        return 2;
    if (strcmp(s, "sin") == 0 || strcmp(s, "cos") == 0 || strcmp(s, "tan") == 0 ||
        strcmp(s, "ln") == 0 || strcmp(s, "lg") == 0 ||
        strcmp(s, "acos") == 0 || strcmp(s, "asin") == 0 || strcmp(s, "atan") == 0)
        return 3;
    if (strcmp(s, "pi") == 0 || strcmp(s, "PI") == 0 || strcmp(s, "Pi") == 0 || strcmp(s, "e") == 0)
        return 4;
    if (strcmp(s, ")") == 0)
        return 2147483647;
    return -1;
}
bool NowCalculate(char n[], stack_array* s) //返回值表示现在是否满足弹出栈帧并开始计算的条件
{
    if (!isEmpty(s))
        return (InLevel(n) <= InLevel(s->Data[s->Top - 1].s) && //当前元素优先级不大于栈顶元素
            strcmp(s->Data[s->Top - 1].s, "(") != 0) ||
            strcmp(n, ")") == 0; 
    else
        return false;
}
bool IsPartOfNumber(char c[], int i) //数字匹配，看看字符串的第i个字符知否属于某个数
{
    int L = strlen(c);
    if (i >= L)
    {
        return false;
    }
    else
    {
        char l, t, n;
        t = c[i];
        l = i - 1 >= 0 ? c[i - 1] : '\0';
        n = i + 1 < L ? c[i + 1] : '\0';
        bool thisIsNum = t >= '0' && t <= '9';
        bool lastIsNum = l >= '0' && l <= '9';
        bool nextIsNum = n >= '0' && n <= '9';
        return (thisIsNum || (lastIsNum && nextIsNum && t == '.') || 
            ((!lastIsNum) && l != ')' && nextIsNum && t == '-'));
    }
}
bool NaturalCut(char c[], int i) //对字符串进行简单地划分，返回值表示在第i个字符处是否应该划分
{
    int L = strlen(c);
    if (i >= L)
    {
        return false;
    }
    else
    {
        char t, n;
        t = c[i];
        n = i + 1 < L ? c[i + 1] : '\0';
        bool thisIsWord = (t >= 'a' && t <= 'z') || (t >= 'A' && t <= 'Z');
        bool nextIsWord = (n >= 'a' && n <= 'z') || (n >= 'A' && n <= 'Z');
        return (thisIsWord != nextIsWord);
    }
}
bool IsObjector(char c[], int i) //判断是否是符号
{
    return (i >= strlen(c)) ?
        false : (
            c[i] == '+' || c[i] == '-' ||
            c[i] == '*' || c[i] == '/' ||
            c[i] == '^' ||
            c[i] == '(' || c[i] == ')') && (!IsPartOfNumber(c, i)
                );
}
void Scanner(char c[], int len);
bool Calculate(stack_array* s, stack_array* n) //具体计算函数，每次弹出一到二个栈帧
{
    if (isEmpty(s))
        return 0;
    char sign[LEN] = { '\0' };
    strcpy(sign, Pop(s).s);
    double d;
    if (strcmp(sign, ")") == 0)
    {
        while (Calculate(s, n)) {};
        return false;
    }
    else if (strcmp(sign, "(") == 0)
    {
        return false;
    }
    else if (strcmp(sign, "+") == 0)
    {
        d = Pop(n).n + Pop(n).n;
    }
    else if (strcmp(sign, "-") == 0)
    {
        double r = Pop(n).n;
        double l = Pop(n).n;
        d = l - r;
    }
    else if (strcmp(sign, "*") == 0)
    {
        d = Pop(n).n * Pop(n).n;
    }
    else if (strcmp(sign, "/") == 0)
    {
        double r = Pop(n).n;
        double l = Pop(n).n;
        d = l / r;
    }
    else if (strcmp(sign, "^") == 0)
    {
        double r = Pop(n).n;
        double l = Pop(n).n;
        d = pow(l, r);
    }
    else if (strcmp(sign, "sqrt") == 0)
    {
        double l = Pop(n).n;
        d = sqrt(l);
    }
    else if (strcmp(sign, "lg") == 0)
    {
        double l = Pop(n).n;
        d = log10(l);
    }
    else if (strcmp(sign, "ln") == 0)
    {
        double l = Pop(n).n;
        d = log(l);
    }
    else if (strcmp(sign, "sin") == 0)
    {
        double l = Pop(n).n;
        d = sin(l);
    }
    else if (strcmp(sign, "cos") == 0)
    {
        double l = Pop(n).n;
        d = cos(l);
    }
    else if (strcmp(sign, "tan") == 0)
    {
        double l = Pop(n).n;
        d = tan(l);
    }
    else if (strcmp(sign, "asin") == 0)
    {
        double l = Pop(n).n;
        d = asin(l);
    }
    else if (strcmp(sign, "acos") == 0)
    {
        double l = Pop(n).n;
        d = acos(l);
    }
    else if (strcmp(sign, "atan") == 0)
    {
        double l = Pop(n).n;
        d = atan(l);
    }
    else if (strcmp(sign, "pi") == 0 || 
        strcmp(sign, "PI") == 0 || 
        strcmp(sign, "Pi") == 0)
        d = M_PI;
    else if (strcmp(sign, "e") == 0)
        d = M_E;
    Push(n, new_dBrick(d));
    printf("%s ", sign);
    return true;
}
void Build(char c[], stack_array* s, stack_array* n) //对输入的整个算式进行计算
{
    int L = strlen(c);
    //char b[L + 1]; //dev C++下此行代码不报错
    char* b = (char*)malloc((L + 1) * sizeof(char));//vs2019 得用这个声明
    b[0] = '\0';
    for (int i = 0; i < L; i++)
    {
        char tp = c[i];
        char th[2] = { tp, '\0' };
        bool cn = IsPartOfNumber(c, i);
        bool ch = IsPartOfNumber(c, i + 1);
        bool se = (tp == ' ' || 
            (ch && (!cn)) ||
            ((!ch) && (!cn) && i + 1 >= L) || (IsObjector(c, i))
            );
        strcat(b, th);
        if (cn && (!ch))
        {
            strcat(b, "");
            if (b[0] != '\0')
            {
                Push(n, new_dBrick(atof(b))); 
                printf("%s ", b);
            }
            b[0] = '\0';
        }
        else if (NaturalCut(c, i) || se)
        {
            strcat(b, "");
            if (b[0] != '\0')
            {
                while (NowCalculate(b, s))
                    Calculate(s, n);
                Push(s, new_sBrick(b));
                b[0] = '\0';
            }
        }
    }
    while (Calculate(s, n)) {};
    printf("\n");
}