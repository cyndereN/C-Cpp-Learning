## 第2章 数字之魅 ———— 数字中的技巧

### 2.1 求二进制数中1的个数

解法1：
```cpp
int Count(BYTE v)
{
    int num = 0;
    while(v){
        if (v%2==1)  num++;
        v /= 2;
    }
    return num;
}
```

解法2：使用位操作

```cpp
int COunt(BYTE v)
{
    int num = 0;
    while(v){
        num += v & 0x01;
        v>>1;
    }
    return num;
}

```
解法3：利用与操作
降到O(M)，M为v中1的个数
```cpp
int Count(BYTE v){
    int num = 0;
    while(v){
        v &= v-1;
        num++;
    }
    return num;
}
```

利用查表法

### 2.2 不要被阶乘吓到

##### 求N的阶乘末尾0的个数

解法1：求出因式分解中5的指数

```cpp
ret = 0;
for(int i = 1; i <= N; i++)
{
    j = i;
    while (j%5==0)
    {
        ret++;
        j /= 5;
    }
}
```

解法2：
```cpp
ret = 0;
while(N) {
    ret += N/5;
    N/=5;
}
```

##### 求最低位1的位置

等同于N!中含有质因数2的个数+1

```cpp
int lowestOne(int n){
    int ret = 0;
    while(N){
        N >> 1;
        ret += N;
    }
}
```

### 2.3 寻找发帖水王

如果一个ID出现次数超过总数N的一半，那么无论水王ID是什么，这个有序列表的第N/2项（从0开始编号）一定是这个ID。

如果不排序的话，每次删除两个不同ID，剩下的ID列表中水王ID出现次数仍然超过总数一半。O(N)复杂度

```cpp
Type Find(Type* ID, int N)
{
    Type candidate;
    int nTimes, i;

    for(i = nTimes = 0; i < N; i++)
    {
        if (nTimes == 0)
            candidate = ID[i], nTimes = 1;
        else
        {
            if (candidate = ID[i])
                nTimes++;
            else
                nTimes--;
        }
    }
    return candidate;
}
```

### 2.4 1的数目

给定十进制正整数N，写下从1开始到N的所有整数，然后输出1的出现次数。

解法1：暴力模拟。O(N lgN)复杂度高

解法2：按位分析规律。e.g., 百位上的数字为0，那么，百位上出现1的次数由更高维决定，等于更高位数字x当前位数。如果百位上为1，出现的次数同时受低位和高位影响。如果百位上数字为2-9，那么百位上出现的次数也受低位影响。O（len(N))

```cpp
LONGLONG Sum1s(ULONGLONG n){
    ULONGLONG iCount = 0;
    ULONGLONG iFactor = 1;
    ULONGLONG iLowerNum = 0;
    ULONGLONG iCurrNum = 0;
    ULONGLONG iHigherNum = 0;

    while (n/iFactor != 0){
        iLowerNum = n-(n/iFactor)*ifactor;
        iCurrNum = (n/iFactor)%10;
        iHigherNum = n / (iFactor*10);

        switch (iCurrNum){
            case 0:
                iCount += iHigherNum * iFactor;
                break;
            case 1:
                iCount += iHigherNum * iFactor + iLowerNum + 1;
                break;
            default:
                iCount += (iHigherNum + 1)* iFactor;
                break;
        }
        iFactor *= 10;
    }

    return iCount;
}
```

###  2.5 寻找最大的k个数

解法1：假设元素数量不大，排序吧。用快排或者堆排序，O(n x logn) + O(k) = O(nlogn)。
用选择和交换排序，把前K个数排序出来O(N x K) 

解法2：快排，随机找的X，把数组分为两部分Sa (>= X), Sb (< X)。

1. Sa中元素个数小于K，Sa中所有的数和Sb中最大的K-|Sa|个元素就是最大的K个数
2. Sa中元素的个数大于等于K，则返回Sa中的K个数。

递归下去，分解成更小的问题。O(N logK)，平均复杂度是线性的

```
Kbig(S,K):
    if(K <= 0)  return []  // 返回空数组

    if(length S <= k):  return S

    (Sa, Sb) = Partition(S)
    return Kbig(Sa, K).Append(Kbig(Sb, K-Sa.length))

Partition(S):
    Sa = []
    Sb = []
    Swap(S[1], S[Random()%S.length])  // 或者洗牌预处理Shuffle, 防止特殊值带来影响
    P = S[1]
    for i in [2: S.length]:
        S[i] > p? Sa.Append(S[i]):Sb.Append(S[i]) 

    Sa.Length < Sb.Length ? Sa.Append(p) : Sb.Append(p)   // p加入较小的，可避免分组失败，也使分组更均匀

    return (Sa, Sb)
```

解法3：维护一个k大小的最小堆，对于数组中的每一个元素判断与堆顶的大小，若堆顶较大，则不管，否则，弹出堆顶，将当前值插入到堆中。时间复杂度O(N logK)。只需要一个K大小的堆，节省内存

解法4：桶排序，完全线性。需要count[MaxN]来记录出现个数，然后扫描一遍。O(N)
```cpp
for(counts = 0, v=MaxN-1; v>=0; v--){
    counts += count[v];
    if (counts >= K)    break;
}

return v;
```

解法5：二分[Smin,Smax]查找结果X，统计X在数组中出现，且整个数组中比X大的数目为k-1的数即为第k大数。时间复杂度平均情况为O(N logN)

解法6：用O(4N)的方法对原数组建最大堆，然后pop出k次即可。时间复杂度为O(4N + KlogN)。
https://www.cnblogs.com/ZeroTensor/p/10559876.html

### 2.6 精确表达浮点数

### 2.7 最大公约数问题

```cpp
int gcd(int x, int y){
    return (!y)? x : gcd(y, x%y);
}
```

取模运算（用到除法）是非常大的开销
因为f(x, y) = f(x-y, y)可得以下解法

```cpp
BigInt gcd(BigInt x, BigInt y){
    if (x<y)  return gcd(y,x);
    if (y==0)  return x;
    else  return gcd(x-y, y);
}
```

注意如果x = p x1, y%p!=0, f(x,y) = f(px1, y) = f(x1,y) 还可以优化


### 2.8 