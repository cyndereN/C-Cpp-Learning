#include<stdio.h>

int main()
{
	int i;
	printf("please enter one number \n");
	scanf("%d",&i);
	if(i<100)
	{
		if(i%2==0)
			printf("%d ��ż��\n",i);
        
		else
		 
			printf("%d ������\n",i);
	 
	}
	else
	 printf("%d Խ���ˣ���������\n",i);
	return 0;
}
