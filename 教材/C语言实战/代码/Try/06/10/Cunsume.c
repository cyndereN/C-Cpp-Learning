#include<stdio.h>
int main()
{
    int money,grade;
	float m;
	float rebate=0.0f ;   
	scanf("%d",&money)  ;                       /*�������money�������Ľ�� m�Ǵ���֮����������*/
        
      grade=money/500;               /*����ȼ�*/
       switch(grade)                           /*���ݵȼ������ۿ�*/
       {
       case 0:
           rebate=0.0f;
           m=money;
           break;
       case 1:
           rebate=0.9f;
           m=money*rebate;
           break;
       case 2:
           rebate=0.8f;
           m=money*rebate;
           break;
       case 4:
           rebate=0.7f;
           m=money*rebate;
           break;
       case 6:
           rebate=0.6f;
           m=money*rebate;
           break;
       case 10:
           rebate=0.5f;
           m=money*rebate;
           break;
       }
       printf("�˿ͽ����ܵ��ۿ�:%f\n",rebate); 
       printf("��ۺ���֧���Ľ��:%f\n",m);
       return 0;
}
