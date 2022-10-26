// f(n) = 1 - 1/2 + 1/3 - 1/4 + 1/5 - 1/6 ...
#include <stdio.h> 
int main(){
	int n,i;
	double sum = 0.0;
	double sign = 1.0;
	scanf("%d",&n);
	for(i=1;i<=n;i++){
		sum += sign/i;
		sign = -sign;
	}
	printf ("f(%d)=%f\n",n,sum);
	return 0;
}  
