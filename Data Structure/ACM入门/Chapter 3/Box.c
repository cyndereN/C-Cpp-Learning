#include <stdio.h>

void swap(int* a, int* b){
    int t;
    t = *a;
    *a = *b;
    *b = t;
}

int main(){
    int a, b;
    int r[6][2];
    int sum[6];

    for(int i=0;i<6;i++){
        scanf("%d %d", &a, &b);
        if(a>b) swap(&a,&b);
        r[i][0]=a;
        r[i][1]=b;
        sum[i] = a + b;
    }   

    printf("\n");
    for(int i=0;i<6;i++){
        printf("%d %d\n", r[i][0], r[i][1]);
    }    

    for(int i=0;i<5;i++)
        for(int j=0;j<5-i;j++){
            if (sum[j]>sum[j+1]) {
                swap(&sum[j],&sum[j+1]);
                swap(&r[j][0],&r[j+1][0]);
                swap(&r[j][1],&r[j+1][1]);
            }
        }

    printf("\n");
    for(int i=0;i<6;i++){
        printf("%d %d\n", r[i][0], r[i][1]);
    }    

    if((r[0][0]==r[1][0])&&(r[1][0]==r[2][0])&&(r[2][0]==r[3][0])&&(r[3][0]==r[0][0])\
        &&(r[0][1]==r[1][1])&&(r[1][1]==r[4][0])&&(r[4][0]==r[5][0])&&(r[5][0]==r[1][1])\
        &&(r[2][1]==r[3][1])&&(r[3][1]==r[4][1])&&(r[4][1]==r[5][1])&&(r[5][1]==r[2][1]))
        printf("Possible.\n");
    else printf("Impossible.\n");

    return 0;
}

