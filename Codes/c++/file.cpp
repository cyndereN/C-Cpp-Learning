#include<stdio.h>
#include<stdlib.h>
#define N 5
struct Player
{
    long num;
    char name[10];
    int Value[3];
}pla[N];
void input(int);
void save(int,char *);
void read(int,char *);
void pla_sort(int);
void insert(int);
int main()
{
    input(N);
    save(N,"player.txt");
    read(N,"player.txt");
    return 0;
}


void input(int n)
{
    int i,j,sum;
    for(i=0;i<n;i++)
    {
        printf("Enter information of player %d\n",i+1);
        printf("Num :");scanf("%ld",&pla[i].num);
        printf("Name :");scanf("%s",pla[i].name);

        for(j=0;j<3;j++)
        {
            printf("Values %d:",j+1);scanf("%d",&pla[i].Value[j]);
        }
    }
}

void save(int n,char *filename)
{
    FILE *fp;
    int i;
    if((fp=fopen(filename,"w"))==NULL)
    {
        printf("cannot create file.\n");
        exit(0);
    }
    for(i=0;i<n;i++)
        if(fwrite(&pla[i],sizeof(struct Player),1,fp)!=1)
            printf("\n error!\n");
    fclose(fp);
}
void read(int n,char *filename)
{
    FILE *fp;
    int i;
    if((fp=fopen(filename,"r"))==NULL)
    {
        printf("cannot open file!\n");
        exit(0);
    }
    for(i=0;i<n;i++)
    {
        fread(&pla[i],sizeof(struct Player),1,fp);
        printf("%ld,%s,%d,%d,%d\n",\
               pla[i].num,pla[i].name,pla[i].Value[0],\
               pla[i].Value[1],pla[i].Value[2]);
    }
    fclose(fp);
}

