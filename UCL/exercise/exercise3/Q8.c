#include <stdio.h>

int main(void){
    int a=0;
    scanf("%d",&a);
    if (factorial(a/100)+factorial((a%100)/10)+factorial(a%10)==a) 
        printf("%d is a strong number.", a);
    else{
        printf("Not a strong number.");
    }
    return 0;
}

int factorial(int n){
    if(n<=0){
        return 1;
    }else{
        return n * factorial(n-1);
    }
}