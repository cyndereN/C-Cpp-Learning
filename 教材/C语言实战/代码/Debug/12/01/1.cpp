#include<stdio.h>

union DataUnion			/*��������������*/
{
	int iInt;			/*��Ա����*/
	char cChar;			
};

int main()
{
	printf("iInt: %d\n", DataUnion);		/*�����Ա��������*/
	printf("cChar: %c\n", DataUnion);
	return 0;
}