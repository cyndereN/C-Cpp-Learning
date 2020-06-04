#include<stdio.h>
int main()
{
	int n;
	int t=0;
	printf("please enter a number:\n");
	
	while(n<100)
	{	
		scanf("%d",&n);
		if(n<100)
		{
			t=t+n;
			n++;
		}
		else
		{
			printf("try <100,asshole");
		}
	}
	printf("%d\n",t);
	return 0;
}
