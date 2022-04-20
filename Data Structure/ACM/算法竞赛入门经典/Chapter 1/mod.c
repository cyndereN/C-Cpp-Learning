#include <stdio.h>
int main(){
    int a,b,c;
    int cnt = 1;
    int flag;
    while(~scanf("%d%d%d",&a, &b, &c)){
        flag = 1;
        for(int i=10;i<=100;i++){
            if(i%3==a && i%5==b && i%7 == c){
                flag = 0;
                printf("Case %d: %d\n", cnt, i);
                break;
            }
        }
        if(flag) printf("Case %d: No answer\n", cnt);
        cnt ++;
    }
    return 0;
}