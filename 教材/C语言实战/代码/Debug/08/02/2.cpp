#include<stdio.h>

int main()
{
	int a[4][5];	/*��������*/
	 int i,j;
	/*�Ӽ���Ϊ����Ԫ�ظ�ֵ*/
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