#include<bits/stdc++.h>
using namespace std;
int main(){
	string s; 
    cin>>s;
	for(int i=0;i<s.size();i++) s[i]=toupper(s[i]);
	cout<<s;
}

//函数原型
int toupper(int c)  
{  
    if ((c >= 'a') && (c <= 'z'))  
        return c + ('A' - 'a');  
    return c;  
}

int tolower(int c)  
{  
    if ((c >= 'A') && (c <= 'Z'))  
        return c + ('a' - 'A');  
    return c;  
}  
