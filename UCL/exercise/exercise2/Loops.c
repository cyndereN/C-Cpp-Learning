#include <stdio.h>
int main(void)
{
 int n = 0;
 for( n = 1 ; n < 11 ; n++){
    printf("%i: A Message\n",n);
 }

 int n = 1;
 do{
    printf("%i: A Message\n",n);
 } while (++n < 11); 

int n = 0;
 while (n++ < 10) {
    printf("%i: A Message\n",n);
 }

 return 0;
}