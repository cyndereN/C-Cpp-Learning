#include <stdio.h>
#include <string.h>

int main(){
    char s[15], c1[7], c2[7];
    while (~scanf("%s", s)){
        int i, j = 0;
        for (i = 0; i < 6; i++){
            c1[i] = s[i];
            c2[i] = s[i + 6];
        }
        int flag;
        for (i = 0; i < 3; i++){ //第一个正方体有三个互相垂直的面 
            flag = 0;
            for (j = 0; j < 6; j++){ //判断是否能在第二个正方体中找到与其相同的两个面					
                if (c1[i] == c2[j] && c1[5 - i] == c2[5 - j]){
                    flag = 1; c2[j] = '0'; c2[5 - j] = '0'; break;
                }
            }
            if (!flag)	break;
        }
        if (!flag)	printf("FALSE\n");
        else printf("TRUE\n");
    }
    return 0;
}