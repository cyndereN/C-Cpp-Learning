//��׳� 


#include <stdio.h>

int main(){
	int n;
	scanf("%d",&n);
	int fact = 1;
	int i = 1;
	for (i=1;i<=n;i++){
		fact *= i; 
	}
	
	//i = n
	//for ( ; n>1 ; n--){
	//	fact * = n
	//}
	//printf("%d!=%d",i,fact);
	
	printf("%d!=%d",n,fact);

}



