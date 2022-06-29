// 通过n-i次关键字的比较，从n-i+1个记录中选择出关键字最小的纪录，并和第i个记录交换之

for (int i = 0; i < length; i++) {
    int minOrMax = i;

    for (int j = i + 1; j < length; j++) {
        if (select == 1) { // 升序
            if (arr[minOrMax] > arr[j]) minOrMax = j;
        }
        else { // 降序
            if (arr[minOrMax] < arr[j]) minOrMax = j;
        }
    }

    // 判断一开始认定的最小或最大值是不是计算的最小值或最大值 如果不是 交换数据
    if (i != minOrMax) {
        int temp = arr[i];
        arr[i] = arr[minOrMax];
        arr[minOrMax] = temp;
    }
}