#include <stdio.h>

int main()
{
    int hun, ten, ind, n;
    printf("Result is: ");
    for( n=100; n<1000; n++ )  {   //987
        hun = n / 100;
        ten = (n-hun*100) / 10;
        ind = n % 10;
        if(n == hun*hun*hun + ten*ten*ten + ind*ind*ind)  
            printf("%d ", n);
    }
    printf("\n");
    return 0;
}