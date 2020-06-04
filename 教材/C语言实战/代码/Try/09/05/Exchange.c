#include<stdio.h>
float fun(int n);
int main()
{
    fun(2); 
	printf("%f\n",s);
    return 0;

}
float fun(int n)
{
    int i;
    float s=0;
    for(i=1;i<=n;i++)
    {
        s=(float)(s+1.0/(i*(i+1)));
      
    }
     
    return (s);
    
     
    
}
