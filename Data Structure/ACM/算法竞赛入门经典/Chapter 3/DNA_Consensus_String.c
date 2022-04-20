#include <stdio.h>
#include <string.h>

int main(){
    int m,n;
    scanf("%d %d",&m,&n) ;
    char c[m+5][n+5];
    for(int i=0;i<m;i++)
        scanf("%s",&c[i]);

            
    int a[4];
    memset(a,0,sizeof(int)*4);
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(c[j][i] == 'A')  a[0]++;
            if(c[j][i] == 'C')  a[1]++;
            if(c[j][i] == 'G')  a[2]++;
            if(c[j][i] == 'T')  a[3]++;    
        }
        if(a[0]>a[1]&&a[0]>a[2]&&a[0]>a[3]) printf("A") ;
        else if(a[1]>a[0]&&a[1]>a[2]&&a[1]>a[3]) printf("C") ;
        else if(a[2]>a[0]&&a[2]>a[1]&&a[2]>a[3]) printf("G") ;
        else printf("T") ;
        memset(a,0,sizeof(int)*4) ;
    }
        
    return 0;
}