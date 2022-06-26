// 查找表：是由同一类型的数据元素（或记录）构成的集合
// 关键字：数据元素中某个数据项的值，又称为键值，用它可以表示一个数据元素。
// 若此关键字可以唯一地表示一个记录，则成为主关键字（primary key）

// 静态查找表：只作查找操作的查找表
// 动态查找表：查找过程中同时插入查找表中不存在的数据元素

// 线性查找优化：不需要每次判断i是否越界，可以设置一个哨兵

int Sequential_Search(int *a, int n, int key) {
    int i;
    a[0] = key; // 也可以设置在末尾
    i = n;  // 循环从尾部开始

    while (a[i]!= key) {
        i--;
    }

    return i;  // 返回0则查找失败
}

// 有序表查找：二分查找
int Binary_Search(int *a, int n, int key) {
    int low, high, mid;
    low = 1; // 下标记录首位
    high = n;

    while(low<=high){
        mid = (low+high)/2;

        if(key<a[mid])
            high = mid - 1;
        else if (key>a[mid])
            low = mid + 1;
        else 
            return mid;
    }

    return 0;
}

// 斐波那契查找，利用黄金分割原理实现