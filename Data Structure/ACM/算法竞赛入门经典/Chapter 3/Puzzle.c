/*
5x5 board, one space, A,B,L,R tom ove the space(end with 0)
Invalid instruction: printf "Puzzle has no final configuration."
print out the board
*/

#include<stdio.h>
#include<string.h>
#define maxn 10005

int main(){
	char a[5][5]={
		'T','R','G','S','J',
		'X','D','O','K','i',
		'M',' ','V','L','N',
		'W','P','A','B','E',
		'U','Q','H','C','F',
	};     

	int len=0;
	char s[maxn], t;
	scanf("%s",s);
	len=strlen(s);
    int i,j;

	for(int m=0;m<5;m++)
		for(int n=0;n<5;n++) // Locate space
			if(a[m][n]==' '){
				i=m;
				j=n;
			}

	for(int k=0;k<len;k++){
		switch(s[k]){
            case 'A': 
                {
                    t=a[i-1][j];
                    a[i-1][j]=a[i][j];
                    a[i][j]=t;
                    i--;
                    break;
                }
            case 'B':  
                {
                    t=a[i+1][j];
                    a[i+1][j]=a[i][j];
                    a[i][j]=t;
                    i++;
                    break;
                }
            case 'L':   
                {
                    t=a[i][j-1];
                    a[i][j-1]=a[i][j];
                    a[i][j]=t;
                    j--;
                    break;
                }
            case 'R':       
                {
                    t=a[i][j+1];
                    a[i][j+1]=a[i][j];
                    a[i][j]=t;
                    j++;
                    break;
                }
            
            case '0':
                break;
                
            default:
                {
                    printf("This puzzle has no final configuration.\n");
                    return 0;
                }
		}
	}
	

	for(i=0;i<5;i++){
		for(j=0;j<5;j++)
			printf("%c",a[i][j]);
		printf("\n");
	}

	return 0;
}
