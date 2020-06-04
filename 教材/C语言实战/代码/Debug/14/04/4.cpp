#include<stdio>

int main()
{
	char cArray[5]={'H','e','l','l','o'};	/*初始化字符数组*/
 	int i;						/*循环控制变量*/
	for(i=0;i<5;i++)			/*进行循环*/
	{
		printf("%c",cArray[i]);	/*输出字符数组元素*/
	}
	printf("\n");				/*输出换行*/
	return 0;
}