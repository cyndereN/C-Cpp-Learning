#include <stdio.h>
#include <string.h>

int h[11][11],v[11][11];

int main()
{
    char ch,s[5];
    int i,j,k,l,n,m,cnt = 1,sum,num,flag;
    while(scanf("%d",&n) != EOF)
    {
        memset(h,0,sizeof(h));
        memset(v,0,sizeof(v));
        sum = 0;
        scanf("%d",&m);
        for(k = 1;k <= m;k++)
        {
            scanf("%c%d%d", &ch, &i, &j);
            if(ch == 'H')
            {
                h[i][j] = 1;
            }
            else if(ch == 'V')
            {
                v[j][i] = 1;
            }
        }

        if(cnt != 1)
        {
            printf("\n**********************************\n\n");
        }
        printf("Problem #%d\n\n",cnt++);

        for(l = 1;l < n;l++)
        {
            num = 0;
            for(i = 1;i+l <= n;i++)
            {
                for(j = 1;j+l <= n;j++)
                {
                    flag = 1;
                    for(k = j;k < j+l;k++)
                    {
                        if(h[i][k] == 0 || h[i+l][k] == 0)
                        {
                            flag = 0;
                            break;
                        }
                    }

                    for(k = i;k < i+l;k++)
                    {
                        if(v[k][j] == 0 || v[k][j+l] == 0)
                        {
                            flag = 0;
                            break;
                        }
                    }
                    num = num + flag;                   
                }
            }
            sum = sum + num;
            if(num > 0)
            {
                printf("%d square (s) of size %d\n",num,l);
            }
        } 
        if(sum == 0)
        {
            printf("No completed squares can be found.\n");
        }

    }

    return 0;
}