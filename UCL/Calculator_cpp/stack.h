#pragma once
#include <stdlib.h>
#define LEN 8
#define SIZE_S 64
#define SIZE_M 128
#define SIZE_L 256
#define SIZE_XL 512
#define SIZE_XXL 1024
union brick {
    double n;
    char s[LEN];
};
brick new_dBrick(double d)
{
    brick b = {d};
    return b;
}
brick new_sBrick(char s[])
{
    brick b;
    for (int i = 0; i < LEN - 1; i++)
    {
        b.s[i] = s[i];
        if (s[i] == '\0')
            break;
    }
    return b;
}
struct stack_array
{
    brick Data[SIZE_M];
    int Top;
};
struct stack_array_L
{
    brick Data[SIZE_L];
    int Top;
};
stack_array CreateStack()
{
    stack_array s;
    s.Top = 0;
    return s;
}
void Push(stack_array *s, brick b)
{
    s->Data[s->Top] = b;
    s->Top++;
}
brick Pop(stack_array *s)
{
    s->Top--;
    return s->Data[s->Top];
}
bool isEmpty(stack_array *s)
{
    return s->Top == 0;
}
bool isFull(stack_array *s)
{
    return s->Top == SIZE_M;
}