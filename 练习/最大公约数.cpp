//���Լ�� 
//ö�ٷ�
/*
#include <stdio.h> 
int main(){
	int a,b; int min;
	scanf("%d %d",&a,&b);
	if(a<b){
		min = a;
	}else{
		min = b;
	}
	
	int ret = 0;
	int i;
	for(i=1;i<=min;i++){
		if(a%i==0&&b%i==0)
		ret = i;
	}
	printf("%d��%d�����Լ����%d.\n",a,b,ret);
}
*/

//շת���
//����a/b����r
//a=b,b=r�����bΪ0����ʱa�������Լ��

#include <stdio.h>
int main(){
	int a,b,t;
	scanf("%d %d",&a,&b);
	while(b!=0){
		t = a%b;
		a=b;
		b=t;
	}
	printf("���Լ����%d.\n",a);
	return 0;
} 
