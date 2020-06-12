/*链表：敌人管理系统*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
 
 
typedef struct P{
    float hp;
    float mp;
    float dmg;
    char name[16];
    struct P* next;
}Player;
 
typedef struct{
    int num;
    Player* next;
}PlayerLinkedList;
 
void AddNewPlayer(PlayerLinkedList *head, Player *newPlayer){
    newPlayer->next = head->next;
    head->next = newPlayer;
    head->num++;
}
 
void RemovePlayer(PlayerLinkedList *head, Player *player){
    Player *p = head->next;
    if (p==player){
        head->next = p->next;
        free(p);
        head->num--;
        return;
    }
    while(p->next != player && p->next != NULL)
        p = p->next;
    if(p->next == player){
        Player *tmp = p->next->next;
        free(p->next);
        p->next=tmp;
        head->num--;
    }
}
 
Player *FindByName(PlayerLinkedList *head,char* name){
    Player *p = head->next;
    while(p != NULL && strcmp(p->name, name)!=0)
        p = p->next;
    return p;
}
 
Player* SortByDMG(Player *first){
    if (first == NULL||first->next == NULL)
        return first;
    Player *minPre = first;
    Player *p = first->next;
    while(p->next != NULL){
        if(p->next->dmg<minPre->next->dmg)
            minPre = p;
        p = p->next;
    }
    if (minPre->next->dmg < first->dmg){
        p = minPre->next;
        minPre->next = p->next;
        p->next = first;
        first=p;
    }
    first->next = SortByDMG(first->next);
    return first;
}
 
void Print(PlayerLinkedList* head){
    Player* p=head->next;
    while(p!=NULL){
        printf("%s,%.2f,%.2f,%.2f\n",p->name,p->hp,p->mp,p->dmg);
        p = p->next;
    }
    printf("\n");
}
 
void Destroy(PlayerLinkedList *head){
    Player* p = head->next;
    Player* q = p->next;
    while(q != NULL){
        q = p->next;
        free(p);
        p = q;
    }
    free(head);
}
 
int main(){
    srand(time(NULL));
    PlayerLinkedList *head = (PlayerLinkedList*)malloc(sizeof(PlayerLinkedList));
    head->next = NULL;
    head->num = 0;
    int nCand = rand()%20;
    char *find = NULL;
    for(int i = 0;i<20;i++){
        Player *p = (Player*)malloc(sizeof(Player));
        p->hp = (rand()%101)/100.0f;
        p->mp = (rand()%101)/100.0f;
        p->dmg = (rand()%101)/100.0f;
        p->name[0] = 'A' + rand()%26;
        p->name[1] = 'A' + rand()%26;
        p->name[2] = 'A' + rand()%26;
        p->name[3] = '\0';
        AddNewPlayer(head,p);
        if(nCand == i)
            find = p->name;
    }
