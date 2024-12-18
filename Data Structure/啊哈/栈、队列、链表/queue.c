//Delete one, the move the next element to the end of queue

#include <stdio.h>
struct queue{
    int data[100];
    int head;
    int tail;
};

int main(){
    struct queue q;
    
    q.head = 1;
    q.tail = 1;
    
    for(int i=1;i<=9;i++){
        scanf("%d",&q.data[q.tail]);
        q.tail++;
    }

    while(q.head < q.tail){
        printf("%d", q.data[q.head]);
        q.head++;

        q.data[q.tail] = q.data[q.head];
        q.tail++;
        q.head++;
    }

    return 0;
}