/*
设某汉字由N × N的0和1的点阵图案组成。

我们依照以下规则生成压缩码。连续一组数值：从汉字点阵图案的第一行第一个符号开始计算，按书写顺序从左到右，由上至下。第一个数表示连续有几个0，第二个数表示接下来连续有几个1，第三个数再接下来连续有几个0，第四个数接着连续几个1，以此类推……

例如: 以下汉字点阵图案：

0001000
0001000
0001111
0001000
0001000
0001000
1111111
对应的压缩码是： 7 3 1 6 1 6 4 3 1 6 1 6 1 3 7 （第一个数是N ,其余各位表示交替表示0和1 的个数，压缩码保证 N × N=交替的各位数之和）

输入格式
一行，压缩码。

输出格式
汉字点阵图（点阵符号之间不留空格）。（3<=N<=200）
*/

#include <bits/stdc++.h>
using namespace std;
#include <iostream>//c++标准库
using namespace std;
int main(){
	int a,n,t=0,i=0,b,s=0;//t判断有没有回车，i判断输出什么，s判断有没有输完
	cin>>n;
	while(s<n*n){
		cin>>a; //循环输入a；
		i++;
		for(b=a;b>=1;b--){
			if(t==n){cout<<endl;t=0;}//判断是否需要回车，回车后t要清零
			if(i%2==1)cout<<0;
            else cout<<1;//判断是否i不被2整除，输出0，否则输出1，注意不要回车
			t++;
			s++;//t与s加一
			}
		}
	cout<<endl;
	return 0;
}