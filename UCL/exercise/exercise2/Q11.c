#include <stdio.h>
#include <math.h>


//a
int main()
{
    int n = 1;
    for (;n<=100;n++) {
        int m = pow(n,2);
        printf("%d\n",m);
    }
    return 0;
}


//b
int main()
{
    int n = 1;
    while (n<=101){
        if (n%2==0){
            int m = pow(n,2);
            printf("%i\n",m);
        } else;
        n++;
    }
}

//c
int main() {
    int i;
    for (i = 2; i <= 100; i++) {
        if (isPrime(i)) {printf("%d\n",i);}
    }
    return 0;
}

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
