// 利用归并的思想，假设初始序列含有n个记录，则可以看成是n个有序的子序列，每个子序列的长度为1，然后两两归并，得到[n/2]
// 个长度为2or1的有序子序列，再两两归并，如此重复，直至得到一个长度为n的有序序列为止

void Merge(int *arr, int n)
{
    int temp[n];    // 辅助数组
    int b = 0;  // 辅助数组的起始位置
    int mid = n / 2;    // mid将数组从中间划分，前一半有序，后一半有序
    int first = 0, second = mid;    // 两个有序序列的起始位置
 
    while (first < mid && second < n)
    {
        if (arr[first] <= arr[second])   // 比较两个序列
            temp[b++] = arr[first++];
        else
            temp[b++] = arr[second++];
    }
 
    while(first < mid)              // 将剩余子序列复制到辅助序列中
            temp[b++] = arr[first++];
    while(second < n)
            temp[b++] = arr[second++];
    for (int i = 0; i < n; ++i)    // 辅助序列复制到原序列
        arr[i] = temp[i];
}
 
void MergeSort(int *arr, int n)
{
    if (n <= 1)    // 递归出口
        return;
    if (n > 1)
    {
        MergeSort(arr, n / 2);    // 对前半部分进行归并排序
        MergeSort(arr + n / 2, n - n / 2);    // 对后半部分进行归并排序
        Merge(arr, n);    // 归并两部分
    }
}
