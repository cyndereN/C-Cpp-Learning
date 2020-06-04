#include<stdio.h>

int main()
{
 
	int iArray[5];
	int i;
	for(i=0;i<5;i++)
	{
	scanf("%d",&iArray[i]);
	}			/*不指定元素个数进行初始化*/
    printf("柠檬%d元一个\n",iArray[0]);
    printf("香蕉单价是%d元\n",iArray[1]);
    printf("苹果单价是%d元\n",iArray[2]);
    printf("圣女果单价是%d元\n",iArray[3]);
    printf("荔枝单价是%d元\n",iArray[4]);
	return 0;
}
