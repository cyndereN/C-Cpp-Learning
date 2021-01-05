#include <cstdio>
#include <algorithm>
using namespace std;

int a[1000];
int main(){
    int m, n, t, cnt=0;
    while(~scanf("%d%d",&m,&n) && m && n){
        for(int i=0;i<m*n;i++) scanf("%d",&a[i]);  //Easier to iterate
        scanf("%d",&t);
        double cub = t*1.0/100;
        sort(a, a+m*n);
        //for(int i=0;i<m*n;i++) printf("%d ",a[i]);
        int sum = 0, i = 0, last = 0;
        double height = 0.0, percentage = 0.0;
        for(i=1;i<m*n && (cub-sum)>0;i++){
            last = sum;
            sum += i*(a[i]-a[i-1]);
        }
        //printf("%d %d %d\n",last,sum,i);
        if(cub == 0) { height = a[0]; percentage =0; }  //No water
        else if(i==m*n && (cub-sum)>0){ //Overflood
            height = (cub-sum)*1.0/i + a[i-1];
            percentage = 100;
        }
        else {                                                  
            height = (cub-last)*1.0/(i-1)+a[i-2];           
            percentage =(i-1)*1.0/(m*n)*100;             
        }
        printf("Region %d\n", ++cnt);
        printf("Water level is %.2f meters.\n", height);
        printf("%.2f percentage  of the region is under water.\n\n", percentage );
    }
    return 0;
}