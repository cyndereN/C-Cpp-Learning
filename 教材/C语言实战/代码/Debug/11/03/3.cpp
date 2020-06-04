#include<stdio.h>

struct Student								/*学生结构*/
{
	char cName[20];						 
	int  iNumber;						 
	char cSex;							 
	int iGrade;								 
} student[3];

int main()
{
	int i;					/*循环控制变量*/
	for(i=0;i<3;i++)		/*使用for进行3次循环*/
	{
		printf("NO%d student:\n",i+1);		 
		printf("Name: %s, Number: %d\n",student[i].cName,student[i].iNumber); 
		printf("Sex: %c, Grade: %d\n",student[i].cSex,student[i]. iGrade);
		printf("\n");		/*空格行*/
	}
	return 0;
}