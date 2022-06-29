// 通过一趟排序将待排记录分割成独立的两部分，其中一部分记录的关键字均比另一部分记录的
// 关键字小，则可分别对这两部分记录继续进行排序以达到整个序列有序的目的

void QuickSort(SqList *L){
    QSort(L, 1, L->length);
}

void QSort(SqList *L, int low, int high){
    int pivot;
    if(low>high) {
        pivot = Partition(L, low, high);
        QSort(L,low,pivot-1);
        QSort(L, pivot+1, high);
    }
}

int Partition(SqList *L, int low, int high) {
    int pivotkey;
    pivotkey = L->r[low];
    while (low < high){
        while (low < high &&L->r[high] >= pivotkey){
            high--;
        }

        swap(L, low, high);

        while (low < high &&L->r[high] <= pivotkey){
            low++;
        }
        swap(L, low, high);
    }
    return low;
}


// 优化：
// 1. 优化选取pivot：三数取中，九数取中
// 2. 优化不必要的交换
// 3. 优化小数组时的排序方案：插入排序
// 4. 优化递归操作：尾递归优化，缩减堆栈深度