/*
题目描述
一般的文本编辑器都有查找单词的功能，该功能可以快速定位特定单词在文章中的位置，有的还能统计出特定单词在文章中出现的次数。

现在，请你编程实现这一功能，具体要求是：给定一个单词，请你输出它在给定的文章中出现的次数和第一次出现的位置。注意：匹配单词时，不区分大小写，但要求完全匹配，即给定单词必须与文章中的某一独立单词在不区分大小写的情况下完全相同（参见样例1），如果给定单词仅是文章中某一单词的一部分则不算匹配（参见样例2 ）。

输入格式
共2行。

第1行为一个字符串，其中只含字母，表示给定单词；

第2行为一个字符串，其中只可能包含字母和空格，表示给定的文章。

输出格式
一行，如果在文章中找到给定单词则输出两个整数，两个整数之间用一个空格隔开，分别是单词在文章中出现的次数和第一次出现的位置（即在文章中第一次出现时，单词首字母在文章中的位置，位置从00 开始）；如果单词在文章中没有出现，则直接输出一个整数-1。
*/
#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
string sent,word;
int lens,lenw,t,pos; 
int main()
{
    getline(cin,word);  
    getline(cin,sent);   //字符串含有空格输入，不可以用cin，否则to me只能读到to 
    lenw=word.size();   
    lens=sent.size();
    for(int i=0;i<lenw;i++)
        word[i]=toupper(word[i]);  //转成大写 
    for(int i=0;i<lens;i++)
        sent[i]=toupper(sent[i]);
    t=0;
    for(int i=0;i<=lens-lenw;i++)
    {
        int j;
        for(j=0;j<lenw;++j)
        {
            if(sent[j+i]!=word[j]) break;
            if(i>0&&sent[i-1]!=' ') break;    //不是单词开头就结束 
            }
            if(j==lenw&&(sent[j+i]==' '||j+i==lens)) //单词长度匹配，后面是空格或者句末 
            {
                t++;
                if(t==1) pos=i;
            }
    }
    if(t==0)cout<<-1;
    else cout<<t<<" "<<pos;
    return 0;
}