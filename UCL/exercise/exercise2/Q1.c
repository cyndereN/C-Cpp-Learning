#include <stdio.h>
int main(void){
    int i = 0;
    while( i++ < 10){
        printf("%d * 13 = %d\n", i, i*13);
    }
    return 0;
}