#include <bits/stdc++.h> 
int n,a,b,c[34],d[8];//a数组代表小明彩票号码，b数组代表中奖号码，d数组代表中N等奖个数 
using namespace std;
int main()
{
	cin>>n;
	for(int i=1;i<=7;i++)//号码有7个
	{
		cin>>b;//输入中奖彩票号码
		c[b]=1; 
	}
	for(int i=1;i<=n;i++)//小明买了n张彩票 
	{
		int sx=0;
		for(int j=1;j<=7;j++)
		{ 
			cin>>a;//输入小明彩票号码 
			if(c[a]==1)sx++;
		} 
		d[7-sx+1]++;//中7-sx+1等奖的计数器+1
	} 
	for(int i=1;i<=7;i++)
	{
		cout<<d[i]<<" ";//输出数组 o(*￣︶￣*)o
	} 
	return 0;//不能忘 o(*￣︶￣*)o
}