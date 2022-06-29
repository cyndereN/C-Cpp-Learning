void BubbleSort(SqList *L){
    int i, j;
    // 优化：避免有序情况下的无意义循环判断
    Status flag = TRUE;
    for(i = 1; i<L-length && flag; i++){
        flag = FALSE;
        for(j=L->length-1;j>=i;j++){
            if(L->r[j] >  L->r[j+1]) // 升序
                swap (L, j, j+1);
                flag = TRUE; // 如果有数据交换，flag为true
        }
    }
}

