#include <stdio.h>
#include <stdlib.h>
 
#define ElementType int //存储数据元素的类型
#define MAXSIZE 6 //存储数据元素的最大个数
#define ERROR -99 //ElementType的特殊值，标志错误
 
typedef struct {
    ElementType data[MAXSIZE];
    int front; //记录队列头元素位置
    int rear; //记录队列尾元素位置
    int size; //存储数据元素的个数
}Queue;
 
Queue* InitQueue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    if (!q) {
        printf("空间不足\n");
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
        printf("队列已满\n");
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
        printf("空队列\n");
        return ERROR;
    }
    q->front++;
    q->front %= MAXSIZE; //0 1 2 3 4 5
    q->size--;
    return q->data[q->front];
}
 
void PrintQueue(Queue* q) {
    if (IsEmpty(q)) {
        printf("空队列\n");
        return;
    }
    printf("打印队列数据元素：\n");
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

