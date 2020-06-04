#include<stdio.h>

int main()
{
	int Y,X;
	int Switch;
	printf("please enter X:");
	scanf("%d",&X);
	if(X<1)
	{
		Switch=1;
	}
	else if (X<10&&X>1)
	{
		Switch=2;
	}	
	else if(X>10)
	{
		Switch=3;
	}
	else
	{   
	    Switch=4;
	}
	switch(Switch)
	{
	case 1:
	
		break;
	case 2:
		Y=2*X-1;
		break;
	case 3:
		Y=3*X-11;
		break;
	case 4:
		printf("wrong number bitch\n");
	default:
		break;
	}
	printf("Y is:%d\n",Y);

	return 0;
}
