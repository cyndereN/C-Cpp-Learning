一、四种基本输入形式
1. 一组输入数据
// 示例：整数求和
#include <stdio.h>
int main()
{
    int a,b;
    scanf("%d %d",&a, &b);
    printf("%d\n",a+b);
}

#include<iostream>
using namespace std;
int main()
{
    int a ,b;
    cin>>a>>b;
    cout<<a+b<<endl;
    return 0;
}

2. 多组输入数据，不说明多少组，直到读至输入文件末尾为止
#include <stdio.h>
int main()
{
    int a,b;
    while (scanf("%d %d",&a, &b) != EOF)
        printf("%d\n",a+b);
}

#include<iostream>
using namespace std;
int main()
{
    int a ,b;
    while (cin>>a>>b)
        cout<<a+b<<endl;
    return 0;
}


3. 多组输入数据，不说明多少组，以某特殊输入为结束标志。
#include <stdio.h>
int main()
{
    int a,b;
    while(scanf("%d %d",&a, &b) &&(a||b))
         printf("%d\n",a+b);
}

#include<iostream>
using namespace std;
int main()
{
    int a ,b;
    while(cin>>a>>b&&(a||b))
    {cout<<a+b<<endl;}
    return 0;
}


4. 多组输入数据，开始输入一个N，接下来是N组数据
#include<stdio.h>
int main()
{
    int a ,b,n;
    scanf("%d",&n);
    while(n--)
    {
        scanf("%d %d",&a, &b);
        printf("%d\n",a+b);
    }
    return 0;
}

#include<iostream>
using namespace std;
int main()
{
    int a ,b,n;
    cin>>n
    while(n--)
    {
     cin>>a>>b;
     cout<<a+b<<endl;
    }
    return 0;
}


二、字符串输入
1、每个字符串中不含空格、制表符及回车
char str1[1000], str2[1000];
scanf("%s%s", str1, str2);

2、字符串中含有空格、制表符，但不含回车
char str[1000];
gets(str);

3、字符串中含回车
在这种情况下，如果没有题目的说明，程序无法知道哪里是字符串的分界。
那么，用scanf("%c",&ch)来读，一边读，一边判断分界条件是否满足，如果满足，则把当前读到的东西存到一个字符串中。

三、输出处理
1. 关于空行（Blank line）

示例：A + B Problem (4)
#include<iostream>
using namespace std;
int main()
{
    int n,sum,a;
    while(cin>>n&&n)
    {
        sum=0;
        while(n--)
        {
            cin>>a;
            sum+=a;
        }
        cout<<sum<<endl;
        cout<<endl;
    }
    return 0;
}

2. 中间有空格
int i;
for (i = 0; i < 10; i++)
{
    printf("%d\n", a);
    if (i != 9)
        printf("\n");
}
