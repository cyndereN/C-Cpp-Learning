//A sequence of numbers, print out number of right position and right number but wrong position

#include <stdio.h>
#define maxn 1010

int main(){
    int n, a[maxn], b[maxn];
    int kase = 0;
    while(scanf("%d",&n)==1 && n){ // n=0 means over
        printf("Game %d:\n", ++kase);
        for(int i=0;i<n;i++) scanf("%d", &a[i]); //The sequence need to guess
        for(;;){
            int A=0, B=0;
            for(int i=0;i<n;i++){
                scanf("%d", &b[i]);
                if(a[i] == b[i])  A++;
            }
            if (b[0]==0)  break; // Stop guessing
        
            for(int d=1; d<=9;d++){
                int c1=0, c2=0; //How many times d turned up in a[n] and b[n]
                for(int i=0;i<n;i++){
                    if(a[i]==d) c1++;
                    if(b[i]==d) c2++;
                }
                if((c1!=0)&&(c2!=0))  B += c2;
                //else continue;
            }
            printf("  (%d,%d)\n", A ,B-A); 
        }
    }
    return 0;
}