#include<stdio.h>

int main()
{
	int iNumber=1,n;	 
	int iSum=1;	
     printf("Enter a number\n");
	 scanf("%d",&n);
    
	for(;iNumber<=n;iNumber++)
	{
		iSum*=iNumber; 
	}
	printf("the result is:%d\n",iSum); 
	return 0;
}
