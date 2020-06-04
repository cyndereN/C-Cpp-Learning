#include<stdio.h>
int main()
{
    int iArray[51];
    int total,i;
	for(i=1;i<52;i++)
	{
		if(i%2==0)
		{
			iArray[i]=-2*i+1;
	
		}
		else
		{
			iArray[i]=2*i-1;
		}
	}
	for(i=1;i<52;i++)  
	{
		total=total+iArray[i];
	}
	printf("%d",total);
      return 0;
}
