//ð�ݷ� 

#include <stdio.h>
int main(){
	int i,j,t;
	int a[10]={5,4,3,2,1,4,2,4,9,1,}; //���滻 
	/*��С�������򣬴��ҵ���ð��*/
	for(i=1;i<10;i++){
		for(j=9;j>=i;j--){
			 if(a[j]<=a[j-1]){
			 	t=a[j];
			 	a[j]=a[j-1];
			 	a[j-1]=t;
			 }
		} 
	}
	
	for(i=0;i<10;i++){
		printf("%d\t",a[i]);
	} 
	return 0;
} 

//ѡ�� 
#include <stdio.h>
int main(){
	int i,j,t,min;
	int a[10]={5,4,3,2,1,4,2,4,9,1,}; //���滻 
	for(i=0;i<10;i++){
		min = a[i];
		for(j=i+1;j<=10;j++){
			 if(a[j]<=min){
				min = a[j];
				t=j;
			 }
		}
		a[t]=a[i];
		a[i]=min; 
	}
	/*��С��������*/
	for(i=0;i<10;i++){
		printf("%d\t",a[i]);
	}  
	return 0;
}

//������
#include <stdio.h>
int main(){
	int i,j,min;
	int a[10]={5,4,3,2,1,4,2,4,9,1,}; //���滻 
	/*��С�������򣬴����ҽ���*/
	for(i=0;i<10;i++){
		min=a[i]; 
		for(j=i+1;j<10;j++){
			 if(a[j]<=a[i]){
			 	min=a[j];
			 	a[j]=a[i];
			 	a[i]=min;
			 }
		} 
	}
	
	for(i=0;i<10;i++){
		printf("%d\t",a[i]);
	} 
	return 0;
} 

//���뷨 
#include <stdio.h>
int main(){
	int i,j,t,pos;
	int a[10]={5,4,3,2,1,4,2,4,9,1,};
	for(i=1;i<10;i++){
		t = a[i];
		for(pos=i-1;pos>=0&&t<=a[j];pos--){
			a[pos+1]=a[pos];
			a[pos]=t;                       //һ������ 
		}
	}
	for(i=0;i<10;i++){
		printf("%d\t",a[i]);
	} 
	return 0;
}
	
