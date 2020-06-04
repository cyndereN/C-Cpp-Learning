#include<stdio.h>

int main()
{
	int a[4][5];	/*定义数组*/
	 int i,j;
	/*从键盘为数组元素赋值*/
	for(i=0;i<5;i++)
	{
		for(j=0;j<4;j++)
		{
		    	a[i][j]=(i+1)+(j+1);
                printf("%d ",a[i][j]);
		}
                printf("\n");
	}
 
	return 0;
}