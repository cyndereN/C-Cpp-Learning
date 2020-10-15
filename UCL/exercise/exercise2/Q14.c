#include <stdio.h>


int main(void)
{
    int column,rows;
    char character;
    printf("Please input columns, rows, character:(press enter after input) ");
    scanf("%i\n%i\n%c",&column,&rows,&character);
    while (rows>0)
    {
        while (column>0){
            printf("%c",character);
            column--;
        }
        rows--;
        printf("\n");
    }
}
