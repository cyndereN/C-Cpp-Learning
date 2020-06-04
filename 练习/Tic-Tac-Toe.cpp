//三连棋盘小游戏 

#include <stdio.h>
int main(){
	const int size = 3;
	int board[size][size];
	int i,j;
	int numofX;
	int numofO;
	int result = -1; //-1:无结果；1：X赢；0：O赢
	
	//读入棋盘
	for(i=0;i<size;i++){
		for(j=0;j<size;j++){
			scanf("%d",&board[i][j]);
		}
	} 
	
	//检查行
	for(i=0;i<size&&result==-1;i++){
		numofX=0;
		numofO=0;
		for(j=0;j<size;j++){
			if(board[i][j]==1){   //X输入以1代替 
				numofX++;
			}else{numofO ++;}
		}
	if(numofX==size) result=1;
	else if(numofO==size) result=0;
	} 
	
	//检查列
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
	
	//检查对角线 
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
