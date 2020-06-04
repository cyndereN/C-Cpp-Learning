#include<stdio.h>

int main()
{
	int iNumber=1;	 
	int iSum=0;		 
 
	for(iNumber=1;iNumber<=100;iNumber++)
	{
		iSum=iNumber+iSum; 
	}
	printf("the result is:%d\n",iSum); 

	return 0;
}
