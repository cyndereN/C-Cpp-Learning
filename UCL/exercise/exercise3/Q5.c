#include<stdio.h>

int main(void){
    int a,b,c;
    char *digit[] = {"Zero","One","Two","Three","Four","Five","Six","Seven","Eight","Nine"};
    scanf("%d",&a);
    printf("%s %s %s",digit[a/100], digit[(a%100)/10],digit[(a%100)%10]);
}