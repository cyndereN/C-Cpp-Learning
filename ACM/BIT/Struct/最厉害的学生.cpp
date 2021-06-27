/*
现有 N(N≤1000) 名同学参加了期末考试，并且获得了每名同学的信息：姓名（不超过 8 个字符的字符串，没有空格）、语文、数学、英语成绩（均为不超过 150 的自然数）。总分最高的学生就是最厉害的，请输出最厉害的学生各项信息（姓名、各科成绩）。如果有多个总分相同的学生，输出靠前的那位。
*/
#include<bits/stdc++.h>
using namespace std;
struct strudent{
	int a,b,c;
	string name;
}students[1000];

int n;
bool cmp(strudent ac,strudent wa)
{
	return ac.a+ac.b+ac.c>wa.a+wa.b+wa.c;
}
int main()
{
	cin>>n;
	for(int i=0;i<n;i++)
	cin>>students[i].name>>students[i].a>>students[i].b>>students[i].c;
	sort(students,students+n,cmp);
	cout<<students[0].name<<" "<<students[0].a<<" "<<students[0].b<<" "<<students[0].c<<endl;
	return 0;
}