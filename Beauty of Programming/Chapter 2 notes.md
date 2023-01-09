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