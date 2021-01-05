//按位正序输出
#include <stdio.h>
int main(){
	int x,mask=1,temp;
	scanf("%d",&x);
	temp = x;
	while(temp>9){
		temp/=10;
		mask*=10;
	}//确定mask位数
	do{
		int d = x / mask;
		printf("%d",d);
		if(mask>9){
			printf(" ");
		}
		x %= mask;
		mask/=10;
	} while (mask>0);
	printf("\n");

} 
