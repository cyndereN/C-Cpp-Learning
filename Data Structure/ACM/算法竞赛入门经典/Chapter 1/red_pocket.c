#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
    int money, n;
    scanf("%d%d",&money, &n);
    char name[25];
    int cnt = 0;
    int get;
    srand((int)time(0));
    while(~scanf("%s", name)){
        cnt ++;
        if (cnt>n) break;
        if (cnt==n) get = money;
        else{
            get = rand()%(money-(n-cnt)*1);
            if (get==0) get = 1;
            money -= get;
        }
        printf("%s get %d yuan\n", name, get);
    }
    printf("Sorry you are late\n");
    return 0;
}