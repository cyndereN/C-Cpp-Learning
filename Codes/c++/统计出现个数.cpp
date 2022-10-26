// 统计出现个数

#include <stdio.h>
int main(){
	const int number = 10; //数组大小 only c99
	int x,i;
	int count [number]={0};
	scanf("%d",&x);
	while(x!=-1){
		if(x>=0&&x<=9){
			count[x]++;
		}
		scanf("%d",&x);
	}
	for(i=0;i<number;i++){
		printf("%d:%d\n",i,count[i]);
	} 
	return 0;
} 
