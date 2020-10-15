#include <stdio.h>
int main(void){
    int i = 1;
    do{
      printf("%d * 13 = %d\n", i, i*13);
    }while( i++ < 10);
    return 0;
}