#include<stdio.h>

struct Product				/*�����ṹ*/
{
	char  Name[10];			 
	char  Shape[20];		 
	char  Color[10];	 
	int	  Price;			 
	char  Area[20];			 
}			

int main()
{
	struct Product product1;			/*����ṹ�����*/

	printf("please enter product's name\n");	/*��Ϣ��ʾ*/
	scanf("%s",&product1. Name);	/*����ṹ��Ա*/

	printf("please enter product's shape\n");/*��Ϣ��ʾ*/
	scanf("%s",&product1. Shape);	/*����ṹ��Ա*/

	printf("please enter product's color\n");/*��Ϣ��ʾ*/
	scanf("%s",&product1. Color);	/*����ṹ��Ա*/

	printf("please enter product's price\n");/*��Ϣ��ʾ*/
	scanf("%d",&product1. Price);	/*����ṹ��Ա*/

	printf("please enter product's area\n");/*��Ϣ��ʾ*/
	scanf("%s",&product1. Area);	/*����ṹ��Ա*/

	printf("Name: %s\n",Name);	/*����Ա�������*/
	printf("Shape: %s\n",Shape);
	printf("Color: %s\n",Color);	
	printf("Price: %d\n",Price);
	printf("Area: %s\n",Area);

	return 0;
}