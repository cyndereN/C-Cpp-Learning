#include <stdio.h>
#include <stdlib.h>
 
#define ElementType int //�洢����Ԫ�ص�����
#define MAXSIZE 6 //�洢����Ԫ�ص�������
#define ERROR -99 //ElementType������ֵ����־����
 
typedef struct {
    ElementType data[MAXSIZE];
    int front; //��¼����ͷԪ��λ��
    int rear; //��¼����βԪ��λ��
    int size; //�洢����Ԫ�صĸ���
}Queue;
 
Queue* InitQueue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    if (!q) {
        printf("�ռ䲻��\n");
        return NULL;
    }
    q->front = -1;
    q->rear = -1;
    q->size = 0;
    return q;
}
 
int IsFull(Queue* q) {
    return (q->size == MAXSIZE);
}
 
void Push(Queue* q, ElementType item) {
    if (IsFull(q)) {
        printf("��������\n");
        return;
    }
    q->rear++;
    q->rear %= MAXSIZE;
    q->size++;
    q->data[q->rear] = item;
}
 
int IsEmpty(Queue* q) {
    return (q->size == 0);
}
 
ElementType Pop(Queue* q) {
    if (IsEmpty(q)) {
        printf("�ն���\n");
        return ERROR;
    }
    q->front++;
    q->front %= MAXSIZE; //0 1 2 3 4 5
    q->size--;
    return q->data[q->front];
}
 
void PrintQueue(Queue* q) {
    if (IsEmpty(q)) {
        printf("�ն���\n");
        return;
    }
    printf("��ӡ��������Ԫ�أ�\n");
    int index = q->front;
    int i;
    for (i = 0; i < q->size; i++) {
        index++;
        index %= MAXSIZE;
        printf("%d ", q->data[index]);
    }
    printf("\n");
}

void DestroyQueue(Queue* q){
    free(q);
}
 
int main(int argc, const char * argv[]) {
    Queue* q = InitQueue();
    
    Push(q, 0);
    Push(q, 1);
    Push(q, 2);
    Push(q, 3);
    Push(q, 4);
    Push(q, 5);
    PrintQueue(q);
    
    Pop(q);
    Pop(q);
    Pop(q);
    PrintQueue(q);
    
    Push(q, 6);
    Push(q, 7);
    Push(q, 8);
    PrintQueue(q);

    DestroyQueue(q);
 
    return 0;
}

