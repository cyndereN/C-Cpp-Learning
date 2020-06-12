//分解质因数
//No.1 
#include <stdio.h>
int prime(int num);
int num;

int main(){
	int num,i,isprime=1;
	
	scanf("%d",&num);
	printf("%d=",num);	
	for(i=2;i<num-1;i++){
		if(num%i==0){
			isprime = 0;
			break;
	}}
	if(isprime==0){
		prime(num);
	}
	
	if(isprime==1){
			printf("%d",num);
	}
	return (0);
}

int prime(int num){
	int i;
	for(i=2;i<num;i++){
		do{
		if(num%i==0){
			printf("%dx",i);
			num=num/i;
			}else{break;}
		}while(num>i);
		}
	    printf("%d",num);
	}

