#include<stdio.h>

union DataUnion			/*声明共用体类型*/
{
	int iInt;			/*成员变量*/
	char cChar;			
};

int main()
{
	printf("iInt: %d\n", DataUnion);		/*输出成员变量数据*/
	printf("cChar: %c\n", DataUnion);
	return 0;
}