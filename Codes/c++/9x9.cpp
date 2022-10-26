#include <stdio.h>

int main(){
	int m=1;
	int n=1;
	for(m=1;m<=9;m++){
		for(n=1;n<=9;n++){
			if(n<m) printf("\t");
			else printf("%d*%d=%-4d",m,n,m*n);
		}
		printf("\n");	
	}
	return 0;
}
