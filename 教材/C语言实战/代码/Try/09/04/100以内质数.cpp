#include <stdio.h>
int main()
{
	int i=0,j=0,n=0,b=0;
	int aa[]={0};
	for(n=2;n<=100;n++)
	{
		for(i=2;i<n;i++){
			if(n%i==0)
			break;
		}
			if(n==i)
			printf("%d\t",n);
			
	}

	return 0;
}
