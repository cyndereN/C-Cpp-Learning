#include <stdio.h>

int main()
{
	int a, temp, n = 0;
	do
	{
		printf("������һ������\n");
		scanf("%d",&a);
		if(a<0) printf("������������\n"); 
	}while(a<0);
	temp = a;
	do
	{
		n=n*10+a%10;
		a/=10;
	}while(a>=1);
	printf("%d",n);
	return 0;
	 
}
