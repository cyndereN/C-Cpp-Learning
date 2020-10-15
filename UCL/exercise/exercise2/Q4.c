#include <stdio.h>
int main(void){
    int i = 0;
    while(i++ < 4){
        if (i==1 || i==4){
            printf("*****\n");
        }else{
            printf("*   *\n");
      }
    }
    return 0;
}