#include <stdio.h>

void println(i){
    int j = 0;
    printf("*");
    for(;j<i-1;j++){printf(" ");};
    if(i==0) printf("\n");
    else printf("*\n");
}

int main(void) {
    int x = 0;
    for(;x<5;x++){
        println(x);
    }
    for(;x>-1;x--){
        println(x);
    }
    return 0;
}
