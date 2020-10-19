#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void){
    
    long num;
    int ret=1;
    char input_num[50]={0};
    

    while(1){
        printf("Please input an integer.\n");
        scanf("%s",&input_num);
        if (strspn(input_num, "0123456789") == strlen(input_num)){
            break;          //Check if user input an integer
        }
    }
    num = atoi(input_num);  //Transfer type string to integer
    if(isPrime(num)) printf("%d is a prime number.", num);
    else {printf("Not a prime number.");}
    return 0;
}



int isPrime(long i){
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