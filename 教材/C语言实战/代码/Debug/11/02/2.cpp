#include<stdio.h>

struct Student					/*ѧ���ṹ*/
{
     cName[20];				 
	 cSex;					 
	 iGrade;					 
} student1={"Ha",'W',3};					/*������������ó�ʼֵ*/


int main()
{
	 
	printf("the student1's information:\n");
	printf("Name: %s\n",student1.cName);
	printf("Sex: %c\n",student1.cSex);
	printf("Grade: %d\n",student1.iGrade);
	return 0;
}