#include<stdio.h>

int main()
{
	int iDay=0;								 

	printf("enter a day of week to get course:\n");	 
	scanf("%d",&iDay);							 

	switch(iDay)
	{
	case 1:		 
		printf("Have a meeting in the company\n");
		continue;
	case 6:			 
		printf("Go shopping with friends\n");
		continue;
	case 7:			 
		printf("At home with families\n");
		continue;
	default:	 
		printf("Working with partner\n");
		break;
	}
	return 0;
}
