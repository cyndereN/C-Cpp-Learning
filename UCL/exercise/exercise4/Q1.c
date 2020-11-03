/*
Write a version of the string copy function that takes a single string argument and creates a
new copy in dynamic (heap) memory. The function signature should be:
    char* stringCopy(char *s)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char* stringCopy(char *s);
int main(){
    char s1[30];
    scanf("%s",s1);
    printf("%s %p\n",s1, s1);
    char* s2 = stringCopy(s1);
    printf("%s %p\n", s2, s2);
    free(s2);
    return 0;
}

char* stringCopy(char *s){
    char* s_copy = calloc(sizeof(s), 1);
    strcpy(s_copy, s);
    return s_copy;
}