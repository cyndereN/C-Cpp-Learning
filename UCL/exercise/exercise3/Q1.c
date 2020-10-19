#include <stdio.h>
#include <math.h>
#define s ((a+b+c)/2)

void main()
{
    float a,b,c;
    double area;
    scanf("%f %f %f",&a,&b,&c);
    if(a >= b+c || b >= a+c || c>=a+b) printf("error\n");
    else{
        area=sqrt((double)(s*(s-a)*(s-b)*(s-c)));
        printf("%f\n",area);
    }
}