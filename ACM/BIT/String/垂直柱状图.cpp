/*题目描述
写一个程序从输入文件中去读取四行大写字母（全都是大写的，每行不超过100个字符），然后用柱状图输出每个字符在输入文件中出现的次数。严格地按照输出样例来安排你的输出格式。

输入格式
四行字符，由大写字母组成，每行不超过100个字符

输出格式
由若干行组成，前几行由空格和星号组成，最后一行则是由空格和字母组成的。在任何一行末尾不要打印不需要的多余空格。不要打印任何空行。
*/
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int ff[26];//定义计数数组
int main()
{
    int i,j,n,maxn=0;char a[81];
    for(i=0;i<4;i++)
    {
        gets(a);//gets读入
        n=strlen(a);
        for(j=0;j<n;j++) if(a[j]>='A'&&a[j]<='Z') ff[a[j]-'A']++;//统计字符出现次数
    }
    for(i=0;i<26;i++)   maxn=max(maxn,ff[i]);//最多次数（最高柱状图）
    for(i=maxn;i>0;i--){
        for(j=0;j<26;j++)
            if(ff[j]>=i)printf("* ");else printf("  ");//模拟，是可以输出的就输出*，否则跳过
        printf("\n");
    }//换行
    for(i=0;i<26;i++)printf("%c ",i+'A');//输出a~z
    return 0;
}