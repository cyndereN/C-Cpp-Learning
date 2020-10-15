//No.1 
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


//No.2 
int isPrime(int i)
{
	int ret = 1;
	int k;
	if(i==1||(i%2==0&&i!=2)) 
		ret=0;
	for( k=3; k<sqrt(i); k+=2 ){
		if( i%k == 0){
			ret = 0;
			break;
		}
	}
	return ret;
}

//No.3 

#include <stdio.h>
int isPrime(int x, int prime[],int number_of_known_primes);
int main(void){
	const int number = 100;
	int prime[number]={2,3};
	int count = 2;
	int i=3;
	int sum=0;
	while(count<number){
		if(isPrime(i,prime,count)){
			prime[count++]=i;
		}
		i+=2;
	}
	
for( i=0; i<number; i++){
	printf("%d",prime[i]);
	if((i+1)%5) printf("\t");
	else printf("\n");
	sum=sum+prime[i];
}                               //Êä³öËØÊý±í ÒÔ¼°ºÍ 
	printf("%d",sum);
	return 0;
}

int isPrime(int x, int prime[],int number_of_known_primes){
	int ret = 1;
	int k;
	for ( k=0; prime[k]<sqrt(x)&&k<number_of_known_primes;k++ ){
		if(x % prime[k]==0)  ret=0; break;
	}
	return ret;
}
