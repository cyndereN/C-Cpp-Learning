#include<stdio.h>
#include<string.h>
int main()
{
    char a;
    char *str=&a;
    strcpy(str,"hello");
    printf(str);
    return 0;
}