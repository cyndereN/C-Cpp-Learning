#include<stdio.h>
int main()
{
    enum
        weekday={Sunday,Monday,Tuesday,Wednesday,Thursday,Friday,Saturday};
    enum weekday a,b,c;
        a=0;
        b=1;
        c=6;
        printf("%d,%d,%d\n",a,b,c);
        return 0;
}