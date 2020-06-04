#include<stdio.h>

struct Product				/*声明结构*/
{
	char  Name[10];			 
	char  Shape[20];		 
	char  Color[10];	 
	int	  Price;			 
	char  Area[20];			 
}			

int main()
{
	struct Product product1;			/*定义结构体变量*/

	printf("please enter product's name\n");	/*信息提示*/
	scanf("%s",&product1. Name);	/*输出结构成员*/

	printf("please enter product's shape\n");/*信息提示*/
	scanf("%s",&product1. Shape);	/*输出结构成员*/

	printf("please enter product's color\n");/*信息提示*/
	scanf("%s",&product1. Color);	/*输出结构成员*/

	printf("please enter product's price\n");/*信息提示*/
	scanf("%d",&product1. Price);	/*输出结构成员*/

	printf("please enter product's area\n");/*信息提示*/
	scanf("%s",&product1. Area);	/*输出结构成员*/

	printf("Name: %s\n",Name);	/*将成员变量输出*/
	printf("Shape: %s\n",Shape);
	printf("Color: %s\n",Color);	
	printf("Price: %d\n",Price);
	printf("Area: %s\n",Area);

	return 0;
}