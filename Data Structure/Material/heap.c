PriorityQueue *initPQ(int);
int isFullPQ(PriorityQueue*);
int isEmptyPQ(PriorityQueue*);
int insertPQ(ElementType, PriorityQueue*);
int findMin(PriorityQueue*, ElementType*);
int deleteMin(PriorityQueue*, ElementType*);
int destoryPQ(PriorityQueue*);

typedef int ElementType;
typedef struct HeapStruct
{
    int capacity;   
    int size;    
    ElementType *elems;  // pq elements array
} PriorityQueue; 

#define true  1
#define false  0
#define SUCCESS 0
#define FAILURE 1

// code for priority queue
PriorityQueue *initPQ(int maxEleNum) {
    PriorityQueue *pq = NULL;
    
    if(maxEleNum <= 0 )
        return NULL;
    pq = malloc(sizeof(PriorityQueue));
    if(pq == NULL) {
        printf("Malloc failed!\n");
        return NULL;
    }
    // index of 0 wil not be in use
    pq->elems = malloc((maxEleNum + 1)*sizeof(ElementType));
    if(pq->elems == NULL) {
        printf("malloc failed\n");
        free(pq);
        return NULL;
    }
    
    // init
    memset(pq->elems, 0, (maxEleNum + 1)*sizeof(ElementType));
    pq->capacity = maxEleNum;
    pq->size = 0;
    return pq;
}

int isFullPQ(PriorityQueue *pq) {
    if(pq == NULL)
        return false;
    if(pq->capacity == pq->size)
        return true;
    else
        return false;
}

int isEmptyPQ(PriorityQueue *pq) {
    if(pqL == NUL)
        return false;
    if(pq->size == 0)
        return true;
    else
        return false;
}

int insertPQ(ElementType value, PriorityQueue *pq) {
    int i = 0;
    
    if(isFullPQ(pq)) {
        printf("PriorityQueue is full\n");
        return FAILURE;
    }
    printf("insert %d\n", value);
    
    // percUp
    for(i = pq->size+1; pq->elems[i/2] > value && i > 1; i/=2) {
        pq->elems[i] = pq->elems[i/2];
    }
    pq->elems[i] = value;
    pq->size++;
    return SUCCESS;
}


int findMin(PriorityQueue *pq, ElementType *value) {
    if(isEmptyPQ(pq)) {
        printf("PriorityQueue is empty\n");
        return FAILURE;
    }
    
    *value = pq->elems[1];
    return SUCCESS;
}

int deleteMin(PriorityQueue *pq, ElementType *min) {
    int i = 1;
    int minChild =0;
    if(isEmptyPQ(pq)) {
        printf("PriorityQueue is empty\n");
        return FAILURE;
    }
    
    *min = pq->elems[1];
    
    ElementType last = pq->elems[pq->size];
    pq->size--;
    if(0 == pq->size) {
        pq->elems[i] = 0;
        return SUCCESS;
    }
    
    // perc down
    for(i = 1;i * 2 <= pq->size;i = minChild) {
        minChild = i * 2;

        if(minChild != pq->size && pq->elems[minChild+1] < pq->elems[minChild])
            minChild+=1;
            
        if(last >pq->elems[minChild])
            pq->elems[i] = pq->elems[minChild];
        else
            break;
    }
    
    pq->elems[i] = last;
    return SUCCESS;
}

int destoryPQ(PriorityQueue *pq) {
    if(NULL == pq)
    {
        return FAILURE;
    }
    free(pq->elems);
    pq->elems = NULL;
    free(pq);
    pq = NULL;
    printf("Destory pq\n");
    return SUCCESS;
}