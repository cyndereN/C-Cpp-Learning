#include<stdio.h>

struct Student								/*ѧ���ṹ*/
{
	char cName[20];						 
	int  iNumber;						 
	char cSex;							 
	int iGrade;								 
} student[3];

int main()
{
	int i;					/*ѭ�����Ʊ���*/
	for(i=0;i<3;i++)		/*ʹ��for����3��ѭ��*/
	{
		printf("NO%d student:\n",i+1);		 
		printf("Name: %s, Number: %d\n",student[i].cName,student[i].iNumber); 
		printf("Sex: %c, Grade: %d\n",student[i].cSex,student[i]. iGrade);
		printf("\n");		/*�ո���*/
	}
	return 0;
}