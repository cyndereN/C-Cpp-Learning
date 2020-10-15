#include <stdio.h>

int main(void) {
    int i = 0, j = 0, m = 0;
    for(;i<6;i++){
        m = 0;
        for(;m<i;m++){printf(" ");}
        for(j=0;j<6-i;j++){printf("*");}
        printf("\n");
    }
    return 0;
}