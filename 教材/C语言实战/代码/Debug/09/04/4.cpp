#include<stdio.h>

int Arrage(int iArray[10])              //定义函数求平均值
{
	int iResult=0;
	int i;
	for(i=0;i<10;i++)
	{
		iResult+=iArray[i];         //求10个数的总数
	}
 
}

int main()
{
	int iStudent[10]={98,67,87,79,82,74,83,86,96,92};
	int iResult;

	iResult=Arrage(iStudent);

	printf("平均成绩是：%d\n",iResult);
	return  0;
}