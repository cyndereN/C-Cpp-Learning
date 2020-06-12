// 求阶乘和
#include <stdio.h>
int main(){
	int i=1,j=1,sum=0,n,p=1;
	scanf("%d",&n);
/*	for(i=1;i<=n;i++){
		for(j=1,p=1;j<=i;j++){
			p = p*j;	
		}
		sum += p;
	} 
*/          //双重循环 
	
	for(i=1;i<=n;i++){
		p *= i;
		sum = sum + p;
	}      //单循环 
	printf ("1到%d的阶乘和是%d",n,sum);
} 
