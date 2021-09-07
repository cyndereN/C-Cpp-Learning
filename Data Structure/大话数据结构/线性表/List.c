/*
ADT线性表(List)
Operation:
    InitList(*L) 初始化操作，建立一个空的线性表L
    ListEmpty(L) 若线性表为空返回true，否则返回false
    ClearList(*L) 将线性表清空
    GetElem(L, i, *e) 将线性表L中第i个位置元素值返回给e
    LocateElem(L, e) 在线性表L中查找与给定值e相等的元素，如果查找成功返回序列号，否则返回0
    ListInsert(*L, i, e) 在线性表L中的第i个位置插入新元素e
    ListDelete(*L, i, *e) 删除线性表L中的第i个位置元素，并用e返回其值
    ListLength(L) 返回线性表L的元素个数
*/

#include <stdio.h>
#define MAXSIZE 20; //储存空间初始分配量
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
typedef int Status;
typedef int ElemType; //ElemType视情况而定，这里假设为int
typedef struct{
    ElemType data[MAXSIZE];
    int length;
}SqList;

Status GetElem(SqList L, int i, ElemType *e){
    /*
        Status是函数的类型，其值是函数结果的状态代码，如OK等；
        初始条件：顺序线性表L已存在，1<=i<=ListLength(L);
        操作结果：用e返回L中第i个数据元素的值；
    */
    if(L.length==0 || i<1 || i>L.length)
        return ERROR;
    *e = L.data[i-1];
    return OK;
}

Status ListInsert(SqList *L, int i, ElemType e){
    // 初始条件：顺序线性表L已存在，1<=i<=ListLength(L);
    // 操作结果：在L中第i个位置之前插入新的数据元素e，L的长度+1;
    int k;
    if(L->length == MAXSIZE) //线性表已满
        return ERROR;
    if(i<1 || i>L->length+1) //当i不在范围
        return ERROR;
    if(i<=L->length){ //若插入数据不在表尾
        for(k=L->length-1 ; k>=i-1 ; k--)
            L->data[k+1] = L->data[k];
    }
    L->data[i-1] = e;
    L->length++;
    return OK;
}

Status ListDelete(SqList *L, int i, ElemType *e){
    // 初始条件：顺序线性表L已存在，1<=i<=ListLength(L);
    // 操作结果：删除L的第i个数据元素，并用e返回其值，L的长度-1；
    int k;
    if(L->length == 0)
        return ERROR;
    if(i<1 || i>L-<length)
        return ERROR;
    *e = L->data[i-1];
    if(i<L->length){
        for(k=1 ; k<L->length ; k++)
            L->data[k-1] = L->data[k];
    }
    L->length--;
    return OK;
}

void unionL(SqList *La, SqList Lb){ //将所有在线性表Lb中但不在La中的数据元素插入到La中
    int La_len, Lb_len, i;
    ElemType e;
    La_len = ListLength(*La);
    Lb_len = ListLength(Lb);
    for(i=1 ; i<=Lb_len ; i++){
        GetElem(Lb, i &e); //取Lb中第i个数据元素赋值给e
        if(!LocateElem(*La, e)) //如果La中不存在和e相同的数据元素
            ListInsert(La, ++La_len, e); //插入
    }
}

//------------------------------------------------------------------------------------
typedef struct Node{
    ElemType data;
    struct Node *next;
} Node;
typedef struct Node *LinkedList;

Status GetElem(LinkedList L, int i, ElemType *e){ // 用e返回L中第i个元素的值
    int j;
    LinkedList p; // 声明指针p
    p = L->next;  // p指向L的第一个节点
    j = 1; // j为计数器
    while(p && j<i){ // p不为空且计数器j还没有等于i，循环继续
        p = p->next;
        ++j;
    }
    if(!p || j>i)
        return ERROR;
    *e = p->data;
    return OK;
}

Status ListInsert(LinkedList *L, int i, ElemType e){
    int j; 
    LinkedList p, s;
    p = *L;
    j = 1;
    while(p && j<i){
        p = p->next;
        j++;
    }
    if(!p || j>i)
        return ERROR;
    s = (LinkedList)malloc(sizeof(Node));
    s->data = e;
    s->next = p->next;
    p->next = s;
    return OK;
}

Status ListDelete(LinkedList *L, int i, ElemType *e){
    int j;
    LinkedList p, q;
    p = *L;
    j = 1;
    while(p->next && j<i){
        p = p->next;
        j++;
    }
    if(!(p->next) || j>i)
        return ERROR;
    q = p->next;
    p->next = q->next;
    *e = q->data;
    free(q);
    return OK;
}

//对于插入和删除数据越频繁的操作，单链表的效率优势就越明显
void CreateListHead(LinkedList *L, int n){  //头插法
    LinkedList p;
    int i;
    srand(time(0));
    *L = (LinkedList)malloc(sizeof(Node));
    (*L)->next = NULL;
    for(i=0 ; i<n ; i++){
        p = (LinkedList)malloc(sizeof(Node));
        p->data = rand()%100+1;
        p->next = (*L)->next;
        (*L)->next = p;
    }
}

void CreateListTail(LinkedList *L, int n){ //尾插法
    LinkedList p, r;
    int i;
    srand(time(0));
    *L = (LinkedList)malloc(sizeof(Node));
    r = *L;
    for(i=0 ; i<n ; i++){
        p = (Node*)malloc(sizeof(Node));
        p->data = rand()%100+1;
        r->next = p;
        r = p; //r又是最后的节点了
    }
    r->next = NULL;
}

Status ClearList(LinkedList *L){
    LinkedList p, q;
    p = (*L)->next;  //p指向第一个节点
    while(p){  //没到表尾
        q = p->next;
        free(p);
        p = q;
    }
    (*L)->next = NULL;
    return OK;
}

//--------------------------------------------------------------------
#define MAXSIZE 1000
typedef struct{
    ElemType data;
    int cur;
}Component, StaticLinkedList[MAXSIZE];

Status InitList(StaticLinkedList space){
    int i;
    for(i=0 ; i<MAXSIZE-1 ; i++)
        space[i].cur = i+1;
    space[MAXSIZE-1].cur = 0; //静态列表为0， 最后一个元素的cur为0
    return OK;
}

int Malloc_SLL(StaticLinkedList space){
    //若备用空间链表非空，则返回分配的结点下标，否则返回0
    int i = space[0].cur; //当前数组第一个元素的cur存的值就是要返回的第一个备用空闲的下标
    if(space[0].cur)
        space[0].cur = space[i].cur; //由于要拿出一个分量来使用了，我们就得把他的下一个分量用来做备用
    return i;
}

Status ListInsert(StaticLinkedList L, int i, ElemType e){
    int j, k, l;
    k = MAXSIZE - 1;
    if(I<1 || i>ListLength(L) + 1)
        return ERROR;
    j = Malloc_SSL(L);
    if(j){
        L[j].data = e;
        for(l=1 ; 1<=i-1 ; l++) //找到第i个元素之前的位置
            k = L[k].cur;
        L[j].cur = L[k].cur;
        L[k].cur = j;
        return OK;
    }
    return ERROR;
}

void Free_SSL(StaticLinkedList space, int k){
    space[k].cur = space[0].cur; //把第一个元素cur值赋给要删除的分量cur
    space[0].cur = k;  //把要删除的分量下标赋值给第一个元素的cur
}

Status ListDelete(StaticLinkedList L, int i){
    int j, k;
    if(i<1 || i>ListLength(L))
        return ERROR;
    k = MAXSIZE - 1;
    for(j=1 ; j<=i-1 ; j++)
        k = L[k].cur;
    j = L[k].cur; //要删除的是j
    L[k].cur = L[j].cur; //要删除的下一个变成前一个的下一个
    Free_SSL(L, j);
    return OK;
}

int ListLength(StaticLinkedList L){
    int j = 0;
    int i = L[MAXSIZE-1].cur;
    while(i){
        i = L[i].cur;
        j++;
    }
    return j;
}

//------------------------------------------------------------
//循环链表的合并
p = rearA->next;
rearA->next = rarB->next->next;
q = rearB->next;
rearB->next = p;
free(q);
//------------------------------------------------------------
typedef struct DuLNode{
    ElemType data;
    struct DuLNode *prior;
    struct DuLNode *next;
} DuLNode, *DuLinkedList;

//插入
s->prior = p;
p->next = s->next;
p->next->prior = s;
p->next = s;

//删除
p->prior->next = p-> next;
p->next->prior = p->prior;
free(p);

