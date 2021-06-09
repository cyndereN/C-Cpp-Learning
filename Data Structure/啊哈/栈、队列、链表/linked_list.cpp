#include <stdio.h>
#include <stdlib.h>
// 创建一个结构体表示链表的结点类型
struct node {
    int data;
    struct node *next;
};

int main(){
    struct node *head, *p, *q, *t;
    int i, n, a;
    scanf("%d", &n);
    head = NULL; //头指针为空
    for(i=0; i<n; i++) { //循环读入n个数
        scanf("%d", &a);
        p=(struct node *)malloc(sizeof(struct node)); //动态申请一个空间，存放节点，用临时指针p指向
        p->data = a;
        p->next = NULL;
        if(head == NULL)  head = p;
        else q->next = p; //上一个节点的后继指针指向p
        q = p;
    }

    scanf("%d", &a); //待插入的数
    t = head;
    while(t != NULL) {
        if (t->next == NULL || t->next->data > a) { //当前节点是最后一个节点或者下一个节点值大于待插入数
            p = (struct node *) malloc(sizeof(struct node));
            p->data = a;
            p->next = t->next;
            t->next = p;
            break;
        }
        t = t->next; //继续下一个节点
    }

    //输出链表中所有数
    t = head;
    while(t!= NULL) {
        printf("%d ", t->data);
        t = t->next;
    }

    return 0;
}