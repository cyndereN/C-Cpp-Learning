# 使用数组实现一个小顶堆

堆也叫优先队列，可以在O(1)时间里得到堆中的最小/大元素。堆在各种编程语言中都有实现，c++STL里面有priority_queue，java中是Priority_Queue，python里提供了heapq模块实现对堆的各种操作。
堆可以分为小顶堆和大顶堆，顾名思义，小顶堆堆顶存储堆中的最小值，大顶堆堆顶存储堆中的最大值，下面使用数组模拟一个小顶堆的实现，大顶堆类似。
要实现一个堆，必须具备add操作(往堆中添加元素)，peek操作(返回堆顶元素)，pop操作(返回堆顶元素并将该元素删除)三个操作，而三个操作又是由up操作和down操作来实现。


up操作将当前元素往上移动，down操作将当前元素往下移动。

```
class Heap {
    int[] heap = new int[1010];//小顶堆
    int sz = 0;//当前堆中的元素数目
    void swap(int a, int b) {
        int c= heap[a];
        heap[a] = heap[b];
        heap[b] = c;
    }

    void up(int u) {
        int f = u / 2;//当前结点的父结点所对应的下标
        //如果当前结点比父结点小 交换当前结点与父结点 并递归处理父结点
        if(f != 0 && heap[f] > heap[u]) {
            swap(f, u);
            up(f);
        }
    }

    void down(int u) {
        int cur = u;
        int l = u * 2;
        int r = u * 2 + 1;
        //如果当前结点比左/右子结点大 交换当前结点与左/右子结点  并递归处理左/右子结点
        if(l <= sz && heap[l] < heap[cur]) cur = l;
        if(r <= sz && heap[r] < heap[cur]) cur = r;
        if(cur != u) {
            swap(cur, u);
            down(cur);
        }
    }

    void add(int x) {
        heap[++sz] = x;//为方便起见 在数组的末尾添加新元素
        up(sz);
    } 

    int peek() {
        return heap[1];//返回堆顶元素
    }

    int pop() {
        int res = heap[1];
        heap[1] = heap[sz--];//将数组结尾元素移至堆顶
        down(1);
        return res;
    }
}

```

建堆优化（Heapify）：

如果你现在有一堆无序数据需要转化成堆，目前你的做法是调用 $n$ 次 add，总复杂度为 $O(n \log n)$。其实存在一种 $O(n)$ 的线性建堆法：直接将数据放入数组，然后从最后一个非叶子节点（下标为 sz/2）开始，倒着往回执行 down 操作。