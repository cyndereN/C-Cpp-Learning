#include<stdio.h>

struct Student								/*学生结构*/
{
	char cName[20];						 
	float fScore[3];						 
}student={"SuYuQun",98.5f,89.0,93.5f};									/*定义变量*/

void Display(student stu)	 
{
 
	printf("Name: %s\n",stu.cName);		/*引用结构成员*/
	printf("Chinese: %.2f\n",stu.fScore[0]);
	printf("Math: %.2f\n",stu.fScore[1]);
	printf("English: %.2f\n",stu.fScore[2]);
	/*计算平均分数*/
	printf("Average score:%.2f\n",(stu.fScore[0]+stu.fScore[1]+stu.fScore[2])/3);
	
}

int main()
{
	Display(student);	/*调用函数，结构变量作为实参进行传递*/
	return 0;
}