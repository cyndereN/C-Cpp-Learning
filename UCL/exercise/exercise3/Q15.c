#include<stdio.h>
void move(int,char,char,char);

int main(){
    //A、B、C represents 3 pillars
    char ch1 = 'A';
    char ch2 = 'B'; 
    char ch3 = 'C'; 

    //n represents the number of plates
    int n;
    printf("Please input the number of plates: ");
    scanf("%d",&n);
    move(n,ch1,ch2,ch3);
    return 0;
}

//Move n plates from x to z using y
void move(int n,char x,char y,char z){
    if(n == 1)
        printf("Plate %d：From %c to %c\n",n,x,z);
    else
    {
        move(n-1,x,z,y);
        printf("Plate %d：From %c to %c\n",n,x,z);
        move(n-1,y,x,z);
    }
}
