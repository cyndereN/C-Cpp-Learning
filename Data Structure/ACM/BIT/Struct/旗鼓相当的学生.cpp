/*
题目描述
现有 N(N\le 1000)N(N≤1000) 名同学参加了期末考试，并且获得了每名同学的信息：姓名（不超过 8 个字符的字符串，没有空格）、语文、数学、英语成绩（均为不超过 150 的自然数）。如果某对学生 <i,j> 的每一科成绩的分差都不大于 5，且总分分差不大于 10，那么这对学生就是“旗鼓相当的对手”。现在我们想知道这些同学中，哪些是“旗鼓相当的对手”？请输出他们的姓名。

所有人的姓名是按照字典序给出的，输出时也应该按照字典序输出所有对手组合。也就是说，这对组合的第一个名字的字典序应该小于第二个；如果两个组合中第一个名字不一样，则第一个名字字典序小的先输出；如果两个组合的第一个名字一样但第二个名字不同，则第二个名字字典序小的先输出。
*/

#include <iostream>
#include <cmath>
using namespace std;
struct node
{
	string name;//名字 
	int a,b,c,s = 0;//三门科的分数与总分 
} students[1005];
int n;
bool cmp(int x,int y);
int main()
{
	cin>>n;
	for(int i = 1;i <= n;i++)
	{
		cin>>students[i].name>>students[i].a>>students[i].b>>students[i].c;
		students[i].s = students[i].a + students[i].b + students[i].c;//求出每个人的总分 
	}
	for(int i = 1;i <= n;i++)//按顺序进行循环，比较 
	{
		for(int j = i + 1;j <= n;j++)
		{
			//选手i，j的比较，如果符合条件便直接输出两个选手的姓名 
			if(cmp(i,j)) cout<<students[i].name<<" "<<students[j].name<<endl;
		}
	}
	return 0;
} 
bool cmp(int x,int y)//每门科目的条件和总分的条件，用"与&"连接 
{
	if(abs(students[x].a - students[y].a) <= 5 && abs(students[x].b - students[y].b) <= 5 && abs(students[x].c - students[y].c) <= 5 && abs(students[x].s - students[y].s) <= 10) return true;
	else return false;
}