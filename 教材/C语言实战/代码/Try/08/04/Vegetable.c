#include<stdio.h>

int main()
{
 
	int iArray[5];
	int i;
	for(i=0;i<5;i++)
	{
	scanf("%d",&iArray[i]);
	}			/*��ָ��Ԫ�ظ������г�ʼ��*/
    printf("����%dԪһ��\n",iArray[0]);
    printf("�㽶������%dԪ\n",iArray[1]);
    printf("ƻ��������%dԪ\n",iArray[2]);
    printf("ʥŮ��������%dԪ\n",iArray[3]);
    printf("��֦������%dԪ\n",iArray[4]);
	return 0;
}
