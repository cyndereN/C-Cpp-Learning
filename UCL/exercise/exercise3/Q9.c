#include <stdio.h>

int main(void){
    int hours, minutes;
    scanf("%d %d", &hours, &minutes);
    if (hours<=11) printf("%d:%0.2dam", hours, minutes);
    else {printf("%d:%0.2dpm", hours, minutes);}
    return 0;
}