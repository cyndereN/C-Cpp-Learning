/*
C6H5OH  94.108 g/mol
*/

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#define maxn 105

double read_char(char c){
    if (c == 'C') return 12.01;
	else if (c == 'H') return 1.008;
	else if (c == 'O') return 16.00;
	else if (c == 'N') return 14.01;
	else return (double)c-'0';
}

int main(){
    char s[maxn];
    scanf("%s", s);

    double m, sum=0;
    
    for(int i=0;i<strlen(s);i++){
        if (isalpha(s[i])) {m = read_char(s[i]); sum += m;}
        else  sum += (read_char(s[i])-1)*m;
    }

    printf("%f g/mol\n", sum);
    return 0;
}