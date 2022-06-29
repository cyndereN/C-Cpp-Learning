// 将一个记录插入到已经排好序的有序表中，从而得到一个新的记录数+1的有序表

void InsertSort(SqList *L) {
    int i, j;
    for(i = 2; i <= L->length(); i++) {
        if(L->r[i] < L->r[i-1]) { // 需将L->r[i]插入有序子表
            L->r[0] = L->r[i]; // L[0]临时储存，设为哨兵
            for(j=i-1 ; L->r[j] > L->r[0] ; j--)
                L->[j+1] = L->r[j];   // 记录后移
            L->r[j+1] = L->r[0];
        }
    }
}