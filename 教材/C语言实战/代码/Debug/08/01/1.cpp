#include<stdio.h>

int main()
{
    int iArray[5], index, temp;				/*定义数组及变量为基本整型*/
    printf("Please enter a Array:\n");

    for (index=0; index<=5; index++)		/*逐个输入数组元素*/
	{
		scanf("%d", &iArray[index]);				
	}
        

    printf("Original Array is:\n");
    for (index = 0; index<=5; index++)			/*显示数组中的元素*/
	{
		printf("%d ", iArray[index]);
	}
    printf("\n");
	return 0;
}
