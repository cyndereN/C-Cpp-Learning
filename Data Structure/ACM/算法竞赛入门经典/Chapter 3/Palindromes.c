#include<stdio.h>
#include<string.h>
#include<ctype.h>

const char* rev = "A   3  HIL JM O   2TUVMXY51SE Z  8 ";
const char* msg[] = {
    "not a palindrome",
    "a regular palindrome",
    "a mirrored string",
    "a mirrored palindrome"
};

//Return reversed character
char r(char ch){
    if(isalpha(ch))// if character is a letter
        return rev[ch-'A']; // 'A' = 0, return index of the reversed letter in rev
    return rev[ch - '0' + 25];
}

int main(){
    char s[30];
    while(scanf("%s",s)==1){
        int len = strlen(s);
        int p=1, m=1;

        for(int i=0;i<(len+1)/2;i++){
            if(s[i] != s[len-1-i])  p=0; // not Palindromes
            if(r(s[i]) != s[len-1-i]) m=0; // not Mirrored
        }
        printf("%s -- is %s.\n\n", s, msg[m*2+p]);
    }
    return 0;
}