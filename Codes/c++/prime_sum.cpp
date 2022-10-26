#include <stdio.h>
#include <math.h>

int prime( int p );
int PrimeSum( int m, int n );

int main()
{
    int m, n, p;

    scanf("%d %d", &m, &n);
    printf("Sum of ( ");
    for( p=m; p<=n; p++ ) {
        if( prime(p) != 0 )
            printf("%d ", p);
    }
    printf(") = %d\n", PrimeSum(m, n));

    return 0;
}
int prime( int p ){
    int ret = 1;
    int i;
    	for( i=2; i<p-1; i++ ){
		if( p%i == 0){
			ret = 0;
			break;
		}
	}
    if (p<=1){ ret = 0 ;}
	return ret;
}
int PrimeSum( int m, int n ){
    int ret = 1;
    int i;
    int p = m ;
    int sum=0;
    while(p>=m&&p<=n){
        if(p<=1){
        	ret = 0;
		}else{
		ret = 1;
    	for( i=2; i<p-1; i++ ){
		if( p%i == 0 ){
			ret = 0;
			break;
		}
	}}
     if (ret == 1) { sum = sum + p; }
     p++;
    }    
    return sum;
}
