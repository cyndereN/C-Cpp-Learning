//最大公约数 
//枚举法
/*
#include <stdio.h> 
int main(){
	int a,b; int min;
	scanf("%d %d",&a,&b);
	if(a<b){
		min = a;
	}else{
		min = b;
	}
	
	int ret = 0;
	int i;
	for(i=1;i<=min;i++){
		if(a%i==0&&b%i==0)
		ret = i;
	}
	printf("%d和%d的最大公约数是%d.\n",a,b,ret);
}
*/

//辗转相除
//计算a/b余数r
//a=b,b=r，如果b为0，此时a就是最大公约数

#include <stdio.h>
int main(){
	int a,b,t;
	scanf("%d %d",&a,&b);
	while(b!=0){
		t = a%b;
		a=b;
		b=t;
	}
	printf("最大公约数是%d.\n",a);
	return 0;
} 
