#include<stdio.h>
 void main()
{
    							 
    int a,b;
    printf("please input a,b:");
    scanf("%d%d",&a,&b);
    //ʵ��2��������
    a^=b;
    b^=a;
    
    printf("a=%d,b=%d\n",a,b);
}
