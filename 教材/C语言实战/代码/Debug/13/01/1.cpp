#include<stdio.h>
 void main()
{
    							 
    int a,b;
    printf("please input a,b:");
    scanf("%d%d",&a,&b);
    //实现2个数交换
    a^=b;
    b^=a;
    
    printf("a=%d,b=%d\n",a,b);
}
