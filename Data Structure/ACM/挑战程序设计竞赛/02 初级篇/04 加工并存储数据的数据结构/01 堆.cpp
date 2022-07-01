// 第i个父节点的左子节点是i*2+1，右子节点是i*2+2

int heap[MAX_N], sz = 0;

// 小顶堆
void push(int x) {
    // 自己节点的编号
    int i = sz++;
    while (i>0){
        // 父节点编号
        int p = (i-1)/2;
        // 如果已经没有大小颠倒则退出 
        if(heap[p] <= x)  break;
        //父节点放下来，自己上浮
        heap[i] = heap[p];
        i = p;
    }

    heap[i] = x;
}

int pop() {
    // 最小值
    int ret = heap[0];

    // 要提到的根的数值
    int x = heap[--sz];

    int i = 0;
    while (i*2+1<sz){
        int a = i*2+1, b = i*2+2;

        if(b<sz && heap[b]<heap[a]) a=b;   // 判断哪个节点小，以及是否有右子节点，与a交换即可

        heap[i] = heap[a];
        i = a;

    }

    heap[i] = x;
    return ret;
    
}