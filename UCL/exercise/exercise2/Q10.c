#include <stdio.h>

int main(void)
{
    int line=1;
    while (line<=8)
    {
        if (line == 1){
            int len = 1;
            while (len<=7) {
                printf("*");
                len++;
            }
        }
        else if (line == 8 ){
            int len = 1;
            while (len<=7){
                printf("*");
                len++;
            }
        }
        else{
            int len = 1;
            while (len<=7){
                if (len == 1)
                    printf("#");
                else if (len == 7)
                    printf("*");
                else if (len == line)
                    printf("*");
                else if (len == line - 1)
                    printf("#");
                else
                    printf(" ");
                len++;
            }

        }
        line++;
        printf("\n");
    }
}