#include<stdio.h>
int main()
{
    int i=0,j=0;
    for(i=9;i>=1;i--)
    {
        for(j=1;j<=9;j++)
        {
            printf("%d*%d=%d\t",i,j,i*j);
        }
    
        printf("\n");
     }
     return 0;
}
