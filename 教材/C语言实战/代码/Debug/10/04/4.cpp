#include <stdio.h>
void sw(int *a,int *b)
{
	int *t;
	*t=*a;
	*a=*b;
	*b=t;
	
}
main()
{
	int x,y;
	int *p_x,*p_y;
	printf("请输入两个数：\n");
	scanf("%d",&x);
	scanf("%d",&y);
	p_x=&x;
	p_y=&y;
	sw(p_x,p_y);
	printf("x=%d\n",x);
	printf("y=%d\n",y);
}
