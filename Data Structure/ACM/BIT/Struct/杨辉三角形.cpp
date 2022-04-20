#include<bits/stdc++.h>
using namespace std;
#define maxn 100010
int yanghui[2][maxn],n;
int main()
{ 
	scanf("%d",&n);
	memset(yanghui,0,sizeof(yanghui));
	for(int i=1;i<=n;i++)
	{
		int k=i%2;//两个数组循环使用
		yanghui[k][i]=1;
		for(int j=1;j<i;j++)
		yanghui[k][j]=yanghui[!k][j]+yanghui[!k][j-1];
  	  
		for(int j=1;j<=i;j++)
		printf("%3d ",yanghui[k][j]);
  	  
		printf("\n");
	}
	return 0; 
} 