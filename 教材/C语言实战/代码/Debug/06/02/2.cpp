#include<stdio.h>

int main()
{
	int i;
	printf("please enter one number \n");
	scanf("%d",&i);
	if(i<100)
	{
		if(i%2==0)
			printf("%d 是偶数\n",i);
        
		else
		 
			printf("%d 是奇数\n",i);
	 
	}
	else
	 printf("%d 越界了！！！！！\n",i);
	return 0;
}
