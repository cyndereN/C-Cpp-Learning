#include<stdio.h>

int main()
{
    int iArray[5], index, temp;				/*�������鼰����Ϊ��������*/
    printf("Please enter a Array:\n");

    for (index=0; index<=5; index++)		/*�����������Ԫ��*/
	{
		scanf("%d", &iArray[index]);				
	}
        

    printf("Original Array is:\n");
    for (index = 0; index<=5; index++)			/*��ʾ�����е�Ԫ��*/
	{
		printf("%d ", iArray[index]);
	}
    printf("\n");
	return 0;
}
