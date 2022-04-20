/* 
abcabcabc 3
*/

#include <stdio.h>
#include <string.h>
#define maxn 85

int main(){
    char s[maxn];
    scanf("%s", s);

    int len = strlen(s);
    for(int i=1;i<len;i++){
        if(len%i==0){
            int T=1;
            for(int j=i;j<len;j++){
                if (s[j]!=s[j%i]) {T=0; break;}
            }

            if(T) {printf("%d\n", i); break;}
        }
    }
    return 0;
}
