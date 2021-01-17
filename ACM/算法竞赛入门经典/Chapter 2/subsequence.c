#include<stdio.h>
#include<math.h>
int main(){
	int n, m;
	double sum = 0;
	while (scanf("%d %d", &n, &m)){
		long long i;
		if (m == 0 && n == 0) break;
		for (i = n; i <= m; i++)
			sum += 1.0 / (i*i);
		printf("%.5f", sum);
	}
	return 0; 
}

//or
#include<stdio.h>
#include<math.h>
int main(){
	int n, m, i;
	double sum = 0;
	while (scanf("%d%d", &n, &m)){
		if (m == 0 && n == 0) break;
		for (i = n; i <= m; i++)
			sum += 1.0 / i / i;
		printf("%.5f", sum);
	}
	return 0;
}