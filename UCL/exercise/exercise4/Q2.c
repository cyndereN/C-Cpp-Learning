/*
Write a function with the signature int strend(char *s, char *t) that returns true (1)
if the string pointed to by t occurs at the end of the string pointed to by s. Otherwise the function
returns false (0).
*/

#include <stdio.h>
#include <string.h>
int is_in(char *s, char *c);
int main()
{
	char str[100];
	char str1[100];
	int length;
	printf("Please input first str str:\n");
	scanf("%s",str);
	printf("Please input second str str1:\n");
	scanf("%s",str1);
	if(is_in(str,str1)){
		printf("Str includes str1\n");
	}else{
		printf("Str does not include str1\n");
	}


}
int is_in(char *s, char *c)
{
    int i=0,j=0,flag=0;
    while(i<strlen(s) && j<strlen(c)){
        if(s[i]==c[j]){//If same, both increase
            i++;
            j++;
        }else{
            i=i-j+1; //Return to the next charactor of the first charactor of last comparing
            j=0;     //Substring restart
        }
        if(j==strlen(c)){ 
            flag=1;  
            break;
        }
    }
    return flag;
}