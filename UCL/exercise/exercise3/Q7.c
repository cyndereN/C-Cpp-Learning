#include <stdio.h>
#define number 200 //Change range here

int main(void){
	int i,no;
	int prime[number];  //Store prime number
	int ptr = 0;

	prime[ptr++] = 2;
	prime[ptr++] = 3;

	for ( no=5; ptr<=number ; no+=2){
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

    printf("\n");
    
    for( i=1; i<number; i++){
        if(prime[i]-prime[i-1]==2) printf("%d %d\n",prime[i-1],prime[i]);
    }
	return 0;
}
