//�ж����� 
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


//No.2 �Ż�1���ų�2�ı������ж������ߵ�ƽ���� 
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

//No.3 �Ż�2: �ж��ܷ���֪��������
//�жϼ����ǰ100������ 
#include <stdio.h>
int main(void){
	int i,no;
	int prime[500];  //Store prime number
	int ptr = 0;

	prime[ptr++] = 2;
	prime[ptr++] = 3;

	for ( no=5; no<=1000 ; no+=2){
		int flag = 0;
		for (i=1;prime[i]*prime[i]<=no;i++){
			if(no%prime[i]==0){
				flag = 1;
				break;
			}
		}
		if(!flag) prime[ptr++] = no;
	}


	for( i=0; i<ptr; i++){
        printf("%d",prime[i]);
        if((i+1)%5) printf("\t");
        else printf("\n");
    } //Print prime table

	return 0;
}





















 
