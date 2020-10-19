#include <stdio.h>
int main(){
	int x,y,s=0;
	scanf("%d",&x);
    y=x;

	do{
		int d = x % 10; 
		printf("%d",d);
		s=s*10+d; 
		x /= 10;
	}while(x>0);
	printf("\n");

    if (y==s) printf("x is a palindrome.");
	
	return 0;
} 