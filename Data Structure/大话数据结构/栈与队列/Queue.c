//循环队列
typedef int QElemType;
typedef struct{
    QElemType data[MAXSIZE];
    int front;
    int rear;
}SqQueue;

Status InitQueue(SqQueue* q){
    Q->front = 0;
    Q->rear= 0;
}

int QueueSize(SqQueue Q){
    return (Q.rear-Q.front+MAXSIZE)%MAXSIZE;
}

Status EnQueue(SqQueue *Q, QElemType e){
    if((Q->rear+1)%MAXSIZE == Q->front) return ERROR;  //队满
    Q->data[Q->rear]=e;
    Q->rear=(Q->rear+1)%MAXSIZE;
    return OK;
}

Status DeQueue(SqQueue *Q, QElemType *e){
    if(Q->front == Q->rear) return ERROR;
    *e=Q->data[Q->front];
    Q->front = (Q->front+1)%MAXSIZE;
    return OK;
}

//链式队列
typedef int QElemType;

typedef struct QNode{
    QElemType data[MAXSIZE];
    struct QNode *next;
}QNode, *QueuePtr;

typedef struct{
    QueuePtr front, rear;
}LinkedQueue;

Status EnQueue(LinkedQueue *Q, QElemType e){
    QueuePtr s = (QueuePtr) malloc(sizeof(QNode));
    if(!s)  exit(OVERFLOW); //存储分配失败
    s->data = e;
    s->next = NULL;
    Q->rear->next = s;
    Q->rear = s;
    return OK;
}

Status DeQueue(LinkedQueue *Q, QElemType *e){
    //头结点的后继节点出队，将头结点的后继改为它后面的结点，若出头结点只剩一个元素，将rear指向头结点
    QueuePtr p;
    if(Q->front = Q->rear) return ERROR;
    p=Q->front->next;
    *e = p->data;
    Q->front->next = p->next;
    if(Q->rear==p)  Q->rear=Q->front;
    free(p);
    return OK;
}