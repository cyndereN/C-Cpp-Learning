#include <stdio.h>

int main(void){
    int day, month, year;
    scanf("%d-%d-%d",&day, &month, &year);
    while (day<1||day>31||month<1||month>12){
        printf("Invalid input.\n");
        scanf("%d-%d-%d",&day, &month, &year);
    }
    if (year%4==0&&year%100!=0||year%400==0)
        printf("It's a leap year.");
    else 
        printf("It's not a leap year.");
    return 0;
}