//��������С��Ϸ 

#include <stdio.h>
int main(){
	const int size = 3;
	int board[size][size];
	int i,j;
	int numofX;
	int numofO;
	int result = -1; //-1:�޽����1��XӮ��0��OӮ
	
	//��������
	for(i=0;i<size;i++){
		for(j=0;j<size;j++){
			scanf("%d",&board[i][j]);
		}
	} 
	
	//�����
	for(i=0;i<size&&result==-1;i++){
		numofX=0;
		numofO=0;
		for(j=0;j<size;j++){
			if(board[i][j]==1){   //X������1���� 
				numofX++;
			}else{numofO ++;}
		}
	if(numofX==size) result=1;
	else if(numofO==size) result=0;
	} 
	
	//�����
	if(result==-1){
		for(j=0;j<size&&result==-1;j++){
		numofX=0;
		numofO=0;
		for(i=0;i<size;i++){
			if(board[i][j]==1){
				numofX++;
			}else{numofO ++;}
		}
	if(numofX==size) result=1;
	else if(numofO==size) result=0;
	} 	
	} 
	
	//���Խ��� 
	if(result==-1){
		numofX=0;
		numofO=0;
		for(i=0;i<size;i++){
			if(board[i][i]==1){
				numofX++;
			}else{numofO ++;}
		}
	if(numofX==size) result=1;
	else if(numofO==size) result=0;
	}	
	
	if(result==-1){
		numofX=0;
		numofO=0;
		for(i=0;i<size;i++){
			if(board[i][size-i-1]==1){
				numofX++;
			}else{numofO ++;}
		}
	if(numofX==size) result=1;
	else if(numofO==size) result=0;
	}		
	
	
	switch(result){
		case -1 : printf("\ndraw\n");
		case 1 : printf("\nX wins.\n");
		case 0 : printf("\nO wins.\n");
	}
	
	
	return 0;
}
