#include<stdio.h>
/*��ʧ;�Ĵ���*/
void Caculate()
{
	static int iSum=3;
	int iTemp;
	iTemp=iSum;			 
	iSum=iTemp*3;
	printf("%d\n",iSum);
}
int main()
{
	Caculate();	 
	Caculate();	 
	return 0;
}

