#include <stdio.h>

void println(i){
    if (i==1||i==7){
        printf("********\n");
    }else if(i==2||i==6){
        printf("*      *\n");
    }else if(i==3||i==5){
        printf("* #### *\n");
    }else{
        printf("* #  # *\n");
    }
}

int main(void) {
    int x = 1;
    for(;x<=7;x++){
        println(x);
    }
    return 0;
}
