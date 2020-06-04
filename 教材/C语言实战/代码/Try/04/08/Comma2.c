#include<stdio.h>
int main()
{
    int y=3,x=3,z=1;
    printf("(%d,%d),%d",(++x,y++),z+x+y+2);
    return 0;
}
