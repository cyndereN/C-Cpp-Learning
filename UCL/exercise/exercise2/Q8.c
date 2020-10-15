#include <stdio.h>

void println(i){
    if (i % 2 == 1){
        printf("*#*#*#\n");
    }else{
        printf("#*#*#*\n");
    }
}

int main(void) {
    int x = 1;
    for(;x<=6;x++){
        println(x);
    }
    return 0;
}
