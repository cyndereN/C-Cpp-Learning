#include <stdio.h>


void printstar(){
    int x = 0;
    while(x++ < 5){
      printf("*");
    }
    printf("\n");
}

int main(void) {
    int i = 0,j = 0;
    for(;i<5;i++){
        for(j=0;j<i;j++){printf(" ");}
        printstar();
    }
    i = 0;
    for(;i<5;i++){
        for(j=5;j>i;j--){printf(" ");}
        printstar();
    }
    
    return 0;
}
