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
			pNew->pNext=pHead;						/*使得指向为空*/
			pEnd=pNew;								/*跟踪新加入的节点*/
			pHead=pNew;								/*头指针指向首节点*/
		}
		else
		{
			pNew->pNext=NULL;						/*新节点的指针为空*/
			pEnd->pNext=pNew;						 
			pEnd=pNew;								 
		}
		pNew=(struct Student*)malloc(sizeof(struct Student));	/*再次分配节点内存空间*/
		scanf("%s",&pNew->cName);
		scanf("%d",&pNew->iNumber);
	}
 										                /*释放没有用到的空间*/
	return pHead;
}

void Print(struct Student* pHead)
{
	struct Student *pTemp;								/*循环所用的临时指针*/
	int iIndex=1;										/*表示链表中节点的序号*/

	printf("----the List has %d members:----\n",iCount);			 
	printf("\n");										/*换行*/
	pTemp=pHead;										/*指针得到首节点的地址*/

	while(pTemp!=NULL)
	{
		printf("the NO%d member is:\n",iIndex);
		printf("the name is: %s\n",pTemp->cName);			/*输出姓名*/
		printf("the number is: %d\n",pTemp->iNumber);			/*输出学号*/
		printf("\n");									/*输出换行*/
		pTemp=pTemp->pNext;							/*移动临时指针到下一个节点*/
		iIndex++;										/*进行自加运算*/
	}
}

int main()
{
	struct Student* pHead;								/*定义头节点*/
	pHead=Create();									/*创建节点*/
	Print(pHead);										/*输出链表*/
	return 0;											/*程序结束*/
}
