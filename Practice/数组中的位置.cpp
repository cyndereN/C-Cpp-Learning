//�ҵ�key�������е�λ��
#include <stdio.h>
int search (int key , int a[], int length);


int main(void)
{
	int a[]={2,4,6,4,3,23,123,56,52,};
	int x;
	int loc;
	scanf("%d",&x);
	loc=search(x,a,sizeof(a)/sizeof(a[0]));
	if(loc!=-1){
		printf("%d�ڵ�%dλ����\n",x,loc);
	}else{
		printf("%d������\n",x);
		return 0;
	}	
} 


int search (int key , int a[], int length)
{
	int ret = -1;
	int i;
	for( i=0; i<length; i++){
		if(a[i]==key)
		ret = i;
	}
	return ret;
}
