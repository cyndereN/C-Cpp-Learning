// ��׳˺�
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
*/          //˫��ѭ�� 
	
	for(i=1;i<=n;i++){
		p *= i;
		sum = sum + p;
	}      //��ѭ�� 
	printf ("1��%d�Ľ׳˺���%d",n,sum);
} 
