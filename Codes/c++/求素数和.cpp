//m~n之间素数和 
#include <stdio.h>
int isPrime(int i)
{
	int ret = 1;
	int k;
	for( k=2; k<i-1; k++ ){
		if( i%k == 0){
			ret = 0;
			break;
		}
	}
	return ret;
}
int main(){
	int m,i,sum=0,cnt=0,n; 
	scanf("%d %d",&m,&n);
	if (m==1)  m=2;
	for(i=m;i<=n;i++){
		if(isPrime(i)){
			sum +=i;
			cnt ++;
		}
	}
	printf("有%d个，和为%d。\n",cnt,sum); 
} 
