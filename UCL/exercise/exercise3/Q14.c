#include <stdio.h>

int main(void){
    int year1,month1,day1,days1=0;
	int year,month,day,days=0;
	int i,j,h,total_days=0;
	int sum=0;
	int leap(int year);
	int monthA[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
	int daysums[20000];
    printf("Input first date.\n");
    scanf("%d-%d-%d",&day1, &month1, &year1);
    while (day1<1||day1>31||month1<1||month1>12){
        printf("Invalid input.\n");
        scanf("%d-%d-%d",&day1, &month1, &year1);
    }
    printf("Input second date.\n");
    scanf("%d-%d-%d",&day, &month, &year);
    while (day<1||day>31||month<1||month>12){
        printf("Invalid input.\n");
        scanf("%d-%d-%d",&day, &month, &year);
    }
    h=year1;
	for(i=1;i<=month1-1;i++)
		{
			days1+=monthA[i];
		}
	
	if (leap(year1)&&month1>=3)
		{
			days1=day1+1+days1;
		}
	else
		{
			days1=day1+days1;
		}
	
	for(j=1;j<=month-1;j++)
		{
			days+=monthA[j];
		}
	if (leap(year)&&month>=3)
		{
			days=day+1+days;
		}
	else
		{
			days=day+days;
		}
	
	if(h==year)
		{
			sum=0;
		}
	else
	{
		for(h=year1;h<year;h++)
			{
				if((h%4==0&&h%100!=0)||h%400==0)
				{	
					daysums[h]=366;
				}
				else
				{	
					daysums[h]=365;
				}
			}
	for(h=year1;h<year;h++)
		{	
			sum=daysums[h]+sum;
		}	
	}
	total_days = sum+days-days1;
    printf("%d", total_days);
    return 0;
}
int leap(int year)
{
	int leap;
	leap=year%4==0&year%100!=0||year%400==0;
	return leap;	
}