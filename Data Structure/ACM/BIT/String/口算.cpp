/*
第一行为数值i

接着的i行为需要输入的算式，每行可能有三个数据或两个数据。

若该行为三个数据则第一个数据表示运算类型，a表示加法运算，b表示减法运算，c表示乘法运算，接着的两个数据表示参加运算的运算数。

若该行为两个数据，则表示本题的运算类型与上一题的运算类型相同，而这两个数据为运算数。

输出格式
输出2*i行。对于每个输入的算式，输出完整的运算式及结果，第二行输出该运算式的总长度
*/
#include <iostream> //cin & cout 用iostream
#include <cstring> //memset & strlen 用cstring
#include <cstdio> //sscanf & sprintf 用cstdio
using namespace std;
int main(){
	char a;//a用于存储运算符
	int n,c,d;//n存储个数不解释，cd存储两个数字
	char s[100],b[10];//s存储最终的字符串，b临时变量
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>b;//输入一串字符，有可能是运算符，也有可能是数字
		if(b[0]>='a' && b[0]<='z'){
			a=b[0];//如果是运算符就存入a，然后输入数字
			cin>>c>>d;
		}else{
			sscanf(b,"%d",&c);//如果是数字就转换b为int存储到第一个数字
			cin>>d;//然后输入剩下的第二个数字
		}
		memset(s,0,sizeof(s));//清空原有的字符串，防止长度判断错误
		if(a=='a')//用sprintf格式化
			sprintf(s,"%d+%d=%d",c,d,c+d);
		else if(a=='b')
			sprintf(s,"%d-%d=%d",c,d,c-d);
		else if(a=='c')
			sprintf(s,"%d*%d=%d",c,d,c*d);
		cout<<s<<endl<<strlen(s)<<endl;//输出字符串和字符串长度
	}
	return 0;
}