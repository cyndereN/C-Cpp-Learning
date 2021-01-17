#include<string>
#include<iostream>

using namespace std;

void pr(string &x,string &y)
{
    string t;
    string r="";
    while(getline(cin,t))
    {
        if(t=="END")break;
        r+=(t+'\n');
    }
    for(int i=0;i<r.size();i++)
    {
        
        if(r[i]!=' '&&r[i]!='\n'&&r[i]!='\t')
        {
            x+=r[i];
        }
        else y+=r[i];
    }

}
int main()
{
    int n;
    cin>>n;
    string s;
    while(n--)
    {   
        string x1,x2,y1,y2;
        cin>>s;
        pr(x1,y1);
        cin>>s;
        pr(x2,y2);

        if(x1==x2&&y1==y2)
        {
            cout<<"Accepted";
        }
        else if(x1==x2&&y1!=y2)
        {
            cout<<"Presentation Error";
        }
        else cout<<"Wrong Answer";
        cout<<endl;
    }
}