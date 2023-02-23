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


### 2.8 找到符合条件的整数

任意给定一个正整数N，求一个最小的正整数M（M>1），使得NxM的十进制表示形式里只有1和0

循环M太耗时间，不如循环NxM再反向找M。对于Mod N同余的数，只需要记录最小的一个。

### 2.9 斐波那契数列
https://github.com/cyndereN/C-Cpp-Learning/blob/master/Data%20Structure/%E4%BB%A3%E7%A0%81%E9%9A%8F%E6%83%B3%E5%BD%95/%E6%80%A7%E8%83%BD%E5%88%86%E6%9E%90/fibonacci.cpp

或用通项公式 O(1)

### 2.10 寻找数组中的最大值和最小值

解法1：扫描一遍，找出最大和最小 2N次比较

解法2：一般来说最大数和最小数不是一个数
比较同一组中奇数位数字和偶数位数字，较大的放到偶数位上，较小的放到奇数位上，再分别求出最大最小。有点像卷积，用一个含有两个数的（一个max，一个min的标尺走一遍） 1.5N次比较

解法3：分治思想，分别求出前后n/2个数最大最小，再取较小的min，较大的max即可。 1.5N次比较

### 2.11 寻找最近点对

解法1：暴力法，两两比较，O(N^2)

解法2：排序，一维情况下，先排序，然后比较相邻的两个点，O(NlogN)

```cpp
double MinDifference(double arr[], int n){
    if(n < 2)   return 0;
    sort(arr, arr+n);

    double fMinDiff = arr[1] - arr[0];

    for(int i=2; i<n; i++){
        if(arr[i] - arr[i-1] < fMinDiff)
            fMinDiff = arr[i] - arr[i-1];
    }
    return fMinDiff;
}
```

扩展到二维情况，先按x排序，然后分治，分别求出左右两边的最小距离，然后求出中间的最小距离，最后取三者的最小值。O(NlogN)

### 2.12 快速寻找满足条件的两个数

解法1：穷举 O(N^2)

解法2：排序，对每个元素arr[i]，花二分查找的时间找到满足条件的arr[j] = sum-arr[i]，O(NlogN) 

解法3：哈希表，O(N)时间 + O(N)空间

```cpp
vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> indices;
        for (int i = 0; i < nums.size(); i++) {
            if (indices.find(target - nums[i]) != indices.end()) { // contains
                return {indices[target - nums[i]], i};
            }
            indices[nums[i]] = i;
        }
        return {};
    }
```

解法4：如果有了数组任意两个元素之和的有序数组（长度为N^2），则可以用二分查找的方法，O(logN)。当然不太可能去计算，因为需要O(N^2)时间。但是可以对两个数字的和做一个有序的遍历，O(NlogN)，在遍历就可以

```cpp
for (i=0; j = n-1; i<j){
    if (arr[i] + arr[j] == sum)  return true;
    else if (arr[i] + arr[j] < sum)  i++;
    else  j--;
}

return false;
    
```

### 2.13 子数组的最大乘积
计算N-1个元素的乘积，然后找出最大的乘积

解法1：记s[i]为前i个元素的乘积，s[i] = s[i-1] * arr[i-1]，s[0]=1（边界条件）
t[i]表示后N-i个元素的乘积，t[i] = t[i+1] * arr[i]，t[N+1]=1（边界条件）
p[i]为数组除第i个元素外，其他N-1个元素的乘积，即：p[i] = s[i-1] * t[i+1]，p[0] = t[1],p[N] = s[N-1]（边界条件）

只需要从头至尾和从尾至头扫描一遍，就可以得到s和t，然后再扫描一遍，就可以得到p，最后找出最大的p即可

O(N)

解法2：分类讨论
假设N个数乘积为p，讨论p正负性

- P=0，说明数组至少1个0，假设去除一个0，其他N-1个数乘积为Q，接着讨论：
    - Q=0, 只能为0
    - Q为正数，返回Q
    - Q为负数，返回0 (用0替换任意一个数，乘积为0，大于负数)

- P为负数
    - 扫描一遍数组，去除最小的负数

- P为正数
    - 扫描一遍数组，如果存在正数，去除最小的正整数，否则去掉绝对值最大的负数


### 2.14 数组的子数组之和的最大值

解法1：O(N^2)

```cpp
int MaxSum(int* A, int n)
{
    int max = -INF;
    int sum;

    for (int i=0; i<n; i++){
        sum = 0;
        for (int j=i; j<n; j++){
            sum += A[j];
            if (sum > max)
                max = sum;
        }
    }

    return max;
}

```


解法2：分治法，O(NlogN)

解法3：动态规划，O(N)

考虑A[0]和{A[i]...A[j]}
- 当0=i=j，A[0]构成最大一段
- 当0=i<j， 和最大的一段以A[0]开始
- 当0<i，元素A[0]不在最大一段中

假设已经知道{A[1]...A[n-1]}的最大一段和为All[1]，并且已经知道(A[1],...A[n-1])中包含A[1]的和最大的一段数组为Start[1]，则有{A[0],...A[n-1]}中问题的解All[0] = max {A[0], A[0]+Start[1], A[1]}

```cpp
int max(int x, int y)
{
    return x > y ? x : y;
}

int MaxSum(int* A, int n)
{
    nStart = A[n-1];
    nAll = A[n-1];

    for (i = n-2; i>=0; i--){
        nStart = max(A[i], A[i]+nStart);
        nAll = max(nAll, nStart);
    }

    return nAll;
}
```


换一种写法
```cpp
int MaxSum(int* A, int n)
{
    nStart = A[n-1];
    nAll = A[n-1];

    for(i=n-2; i>=0; i--){
        if (nStart < 0)
            nStart = 0;
        nStart += A[i];
        if (nStart > nAll)
            nAll = nStart;
    }

    return nAll;
}
```


### 2.15 数组的子数组之和的最大值（二维）

### 2.16 求数组中的最长递增子序列

解法1：O(N^2)

分析1,-1,2,-3,4,-5,6,-7
使用i表示当前遍历的位置
当i=1时，最长递增子序列为1
当i=2时，-1<1，因此必须丢弃第一个值然后重新建立串，当前递增序列为(-1)，长度为1
当i=3时，2>1,2>-1，因此可以在当前递增序列的基础上增加一个2，当前递增序列为(-1,2)，长度为2，之前时1还是-1对后面没影响

```csharp
int LIS(int[] array)
{
    int[] LIS = new int[array.Length];
    for(int i=0; i<array.length; i++){
        LIS[i] = 1;

        for(int j = 0; j<i; j++){
            if(array[j]<array[i] && LIS[j]+1>LIS[i])
                LIS[i] = LIS[j] + 1;
        }
    }
    return Max(LIS);
}
```

解法2：之前不考虑前i个元素，这次考虑。如果之前任意一个子序列的最大的元素比array[i+1]小，那么就可以将array[i+1]加载这个字序列的后面，构成一个新的递增子序列
可以假设：长度为1的递增子序列最大元素最小值为MaxV[1];
长度为2的递增子序列最大元素的最小值为MaxV[2];
长度为LIS[i]的递增子序列最大元素的最小值为MaxV[LIS[i]]
O(N^2)
```csharp
int LIS(int[] array){
    // 记录数组中的递增序列信息
    int[] MaxV = new int[array.Length+1];

    MaxV[1] = array[0];
    MaxV[0] = Min(array)-1;  // 数组中的最小值，边界值

    int[] LIS = new int[array.Length];

    // 初始化最长递增序列的信息
    for(int i=0; i<array.Length; i++){
        LIS[i] = 1;
    }

    int nMaxLIS = 1; // 数组最长递增子序列长度
    for(int i=1; i<array.Length; i++){
        // 遍历历史最长递增序列信息
        int j;
        for (j=nMaxLIS; j>=0; j--){
            if (MaxV[j] < array[i]){
                LIS[i] = j+1;
                break;
            }
        }

        // 如果当前最长序列大于最长递增序列长度，更新最长信息
        if(LIS[i] > nMaxLIS){
            nMaxLIS = LIS[i];
            MaxV[nMaxLIS] = array[i];
        }
        else if (MaxV[j] < array[i] && array[i] < MaxV[j+1]){
            MaxV[j+1] = array[i];
        }
    }

    return nMaxLIS;
}

```

根据单调递增关系，可以将上面方法中的穷举部分进行如下修改O(NlogN)
```
for(j = LIS[i-1]; j>= 1;j--){
    if(array[i]>MaxV[j]){
        LIS[i] = j+1;
        break;
    }
}
```