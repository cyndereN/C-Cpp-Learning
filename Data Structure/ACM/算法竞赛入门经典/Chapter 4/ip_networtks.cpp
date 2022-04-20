#include <cstdio>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
 
int mask_table[] = {255, 254, 252, 248, 240, 224, 192, 128, 0};
int ip[4][1024];
 
int main()
{
    int m;
    while(scanf("%d",&m)!=EOF){
        memset(ip,0,sizeof(ip));
        //输入ip地址 
        for(int i = 0;i < m;i++){
            scanf("%d.%d.%d.%d",&ip[0][i],&ip[1][i],&ip[2][i],&ip[3][i]);
        }
        
        int mask[4];        //用来存储掩码 
        int minip[4];
        //排序每部分的ip地址
        for(int i = 0;i < 4;i++){
            sort(ip[i],ip[i]+m);
            int max = ip[i][m-1];
            int min = ip[i][0];
            int dif = 0;    //存储最后几位不同 
            for(int j = 1;j <= 8;j++){
                if(min%2 != max%2){
                    dif = j;
                }
                min /= 2;
                max /= 2;
            }
            mask[i] = mask_table[dif];  
        }
        
        for(int i = 0;i < 4;i++){
            if(mask[i] != 255){
                for(int j = i+1;j < 4;j++){
                    mask[j] = 0;
                }
                break;
            }
        }
        
        for(int i = 0;i < 4;i++){
            minip[i] = ip[i][0] & mask[i];
        }
        
        printf("%d.%d.%d.%d\n",minip[0],minip[1],minip[2],minip[3]);
        printf("%d.%d.%d.%d\n",mask[0],mask[1],mask[2],mask[3]);
    }       
    return 0;
}