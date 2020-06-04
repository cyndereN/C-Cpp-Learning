#include<stdio.h>
int main()
{
    enum
        weekday={Sunday,Monday,Tuesday,Wednesday,Thursday,Friday,Saturday};
    enum weekday a,b,c;
        a="Sunday";
        b="Monday";
        c="Saturday";
        printf("%d,%d,%d\n",a,b,c);
        return 0;
}