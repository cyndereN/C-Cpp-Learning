#include<stdio.h>

int main()
{
	char cGrade; 
	printf("please enter your grade\n"); 
	scanf("%c",&cGrade);	 
	printf("Grade is about:");	 
	switch(cGrade)		 
	{
	case 'A':	 
		printf("90~100\n");		 
	 		 
	case 'B':		 
		printf("80~89\n");	 
	  
	case 'C':		 
		printf("70~79\n");	 
	 		 
	case 'D':	 
		printf("60~69\n");	 
	 	 
	case 'F':		 
		printf("<60\n");	 
	 	 
 
	}
	return 0;
}