#include<stdio.h>
#include<stdlib.h>

struct Student
{
	char cName[20];								 
	int iNumber;										 
	struct Student* pNext;								 
};

int iCount;												 
struct Student* Create()
{
	struct Student* pHead=NULL;							 
	struct Student* pEnd,*pNew;
	iCount=0;											 
	pEnd=pNew=(struct Student*)malloc(sizeof(struct Student));
	printf("please first enter Name ,then Number\n");
	scanf("%s",&pNew->cName);
	scanf("%d",&pNew->iNumber);
	while(pNew->iNumber!=0)
	{
		iCount++;
		if(iCount==1)
		{
			pNew->pNext=pHead;						/*ʹ��ָ��Ϊ��*/
			pEnd=pNew;								/*�����¼���Ľڵ�*/
			pHead=pNew;								/*ͷָ��ָ���׽ڵ�*/
		}
		else
		{
			pNew->pNext=NULL;						/*�½ڵ��ָ��Ϊ��*/
			pEnd->pNext=pNew;						 
			pEnd=pNew;								 
		}
		pNew=(struct Student*)malloc(sizeof(struct Student));	/*�ٴη���ڵ��ڴ�ռ�*/
		scanf("%s",&pNew->cName);
		scanf("%d",&pNew->iNumber);
	}
 										                /*�ͷ�û���õ��Ŀռ�*/
	return pHead;
}

void Print(struct Student* pHead)
{
	struct Student *pTemp;								/*ѭ�����õ���ʱָ��*/
	int iIndex=1;										/*��ʾ�����нڵ�����*/

	printf("----the List has %d members:----\n",iCount);			 
	printf("\n");										/*����*/
	pTemp=pHead;										/*ָ��õ��׽ڵ�ĵ�ַ*/

	while(pTemp!=NULL)
	{
		printf("the NO%d member is:\n",iIndex);
		printf("the name is: %s\n",pTemp->cName);			/*�������*/
		printf("the number is: %d\n",pTemp->iNumber);			/*���ѧ��*/
		printf("\n");									/*�������*/
		pTemp=pTemp->pNext;							/*�ƶ���ʱָ�뵽��һ���ڵ�*/
		iIndex++;										/*�����Լ�����*/
	}
}

int main()
{
	struct Student* pHead;								/*����ͷ�ڵ�*/
	pHead=Create();									/*�����ڵ�*/
	Print(pHead);										/*�������*/
	return 0;											/*�������*/
}
