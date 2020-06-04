#include <stdio.h>
#include <string.h>
int main()
{
    char arr1[1024];
    char arr2[1024]="good";
    strcat(arr1,arr2);
    printf("arr1=%s",arr1);
    return 0;
}
