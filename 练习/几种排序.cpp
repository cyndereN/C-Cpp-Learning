//冒泡法 

#include <stdio.h>
int main(){
	int i,j,t;
	int a[10]={5,4,3,2,1,4,2,4,9,1,}; //可替换 
	/*从小到大排序，从右到左冒泡*/
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

//选择法 
#include <stdio.h>
int main(){
	int i,j,t,min;
	int a[10]={5,4,3,2,1,4,2,4,9,1,}; //可替换 
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
	/*从小到大排序*/
	for(i=0;i<10;i++){
		printf("%d\t",a[i]);
	}  
	return 0;
}

//交换法
#include <stdio.h>
int main(){
	int i,j,min;
	int a[10]={5,4,3,2,1,4,2,4,9,1,}; //可替换 
	/*从小到大排序，从左到右交换*/
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

//插入法 
#include <stdio.h>
int main(){
	int i,j,t,pos;
	int a[10]={5,4,3,2,1,4,2,4,9,1,};
	for(i=1;i<10;i++){
		t = a[i];
		for(pos=i-1;pos>=0&&t<=a[j];pos--){
			a[pos+1]=a[pos];
			a[pos]=t;                       //一点点插入 
		}
	}
	for(i=0;i<10;i++){
		printf("%d\t",a[i]);
	} 
	return 0;
}
	
