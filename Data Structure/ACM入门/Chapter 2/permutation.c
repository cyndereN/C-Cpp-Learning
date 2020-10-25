#include<stdio.h>
int fun(int a[], int n)
{
	int i, j, k=0;
	for(i = 0; i < n-1; i++){       
        for(j = i+1; j < n; j++)
        {
            if(a[i]==a[j]||a[j]==0)//让每两个数都比教一次，如果发现有 
            return 0;			//相同的或某个数值为零则这组数有问题 
        }
        if(i == n-2&&j==n-1)	//当i等于倒数第二个数，j等于最后一个数时 
        {						//说明所有的数都遍历了一遍 
            return 1;
        }
    }
}
int main()
{
	int a[9],i,j,temp;
	for(i = 123; i <= 329; i++)
	{
		temp = i;			//设置临时变量将i的值赋给他 
		for(j = 0; j < 9; j++)	//将各个位数分离出来存储在数组之中 
		{
			a[j] = temp%10;
			temp /= 10; 
			if(temp==0&&j==2)
			    temp = 2*i;
			if(temp==0&&j==5)
			    temp = 3*i;
		}
		if(fun(a,9)!=0)
			printf("%d %d %d\n",i,2*i,3*i);	
	}
    return 0;
}