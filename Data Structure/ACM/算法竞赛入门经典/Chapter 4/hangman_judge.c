#include <stdio.h>
#include <string.h>
#define maxn 100
int left, chance;
char s[maxn], s1[maxn];
int win, lose; //Flag of win or lose

void guess(char c){
    int wrong = 1;
    for(int i=0;i<strlen(s);i++){
        if(s[i]==c) {left--; s[i] = ' '; wrong = 0;}; //No repeat guess
    }
    if(wrong)  chance--;
    if(!chance)  lose = 1;
    if(!left)  win = 1;
}

int main(void) {
    int rnd = 0;
    while(scanf("%d%s%s", &rnd, s, s1)==3 && rnd != -1){
        printf("Round %d:\n", rnd);
        win = lose = 0;
        left = strlen(s);
        chance = 7;

        for(int i=0;i<strlen(s1);i++){
            guess(s1[i]);
            if(win || lose)  break;
        }

        if(win)  printf("You win.\n");
        else if(lose)  printf("You lose.\n");
        else printf("You chickened out.\n");
    }
    return 0;
}

