#include <stdio.h>
int main(){
	int dxs[101]={0};
	int C_temp,i,j,k,h;
	int cnt=0;
	int sum =0;
	int mi;
for(h=0;h<2;h++){
while(scanf("%d %d",&mi,&C_temp)){
	dxs[mi]=dxs[mi]+C_temp;
	if(mi==0) break;
}
}
for(k=100;k>-1;k--){
	if(dxs[k]!=0) sum++;
}
for(j=100;j>-1;j--){
	if(dxs[j]!=0){
	if(j!=0)printf("%dx%d",dxs[j],j);
	if(j==0)printf("%d",dxs[j]);	
	cnt++;
}

	if(cnt<sum&&dxs[j]!=0){
	printf("+");
	}	
}
return 0;
}
