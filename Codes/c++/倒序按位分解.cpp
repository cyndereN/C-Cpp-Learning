//按位分解整数


 
#include <stdio.h>
int main(){
	int x;
	scanf("%d",&x);
	do{
		int d = x % 10; 
		//int t = t*10+d; 倒序 其他位没有0
		printf("%d",d);
		if (x>9) //or (x>=10)
		{  
			printf (" ");
		} 
		x /= 10;
	}while(x>0);
	printf("\n");
	
	return 0;
} 
