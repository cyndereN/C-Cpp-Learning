## 第3章 结构之法 ———— 字符串及链表的探索

### 3.1 字符串移位包含问题

解法1：对s1进行循环移位，然后判断是否包含s2

```cpp
char src[] = "AABBCD";
char des[] = "CDAA";

int len = strlen(src);
for(int i=0; i<len; i++){
    char temp = src[0];
    for(int j=0; j<len-1; j++){
        src[j] = src[j+1];
    }

    src[len-1] = temp;

    if(strstr(src, des) == 0){
        return true;
    }
}

return false;

```

解法2：将s1+s1，然后判断是否包含s2。
以s1 = ABCD为例，ABCD -> ABCDABCD，s1循环移动的子串都是s1+s1的子串。

### 3.2 电话号码对应英文单词

### 3.3 计算字符串的相似度
定义操作为：1.修改一个字符 2.删除一个字符 3.插入一个字符
使两个字符串达成一致的操作数定义为距离，而相似度等于“距离+1”的倒数

考虑如何把这个问题转化为规模较小的问题。如果两个串第一个字符相同，只要计算第二个字符之后的字符串距离
如果不同，有如下操作：
1.一步操作之后，将A[2..lenA] 和 B[1..lenB]变为一致
2.一步操作之后，将A[1..lenA] 和 B[2..lenB]变为一致
3.一步操作之后，将A[2..lenA] 和 B[2..lenB]变为一致

递归程序
注意该程序递归时会有两个子问题被重复计算

```cpp
Int CalculateStringDistance(string strA, int pABegin,int pAEnd, string strB, int pBBegin, int pBEnd)
{
    if(pABegin > pAEnd){
        if(pBBegin > pBEnd)
            return 0;
        else
            return pBEnd - pBBegin + 1;
    }

    if(pBBegin > pBEnd){
        if(pABegin > pAEnd)
            return 0;
        else
            return pAEnd - pABegin + 1;
    }

    if(strA[pABegin] == strB[pBBegin]){
        return CalculateStringDistance(strA, pABegin+1, pAEnd, strB, pBBegin+1, pBEnd);
    }
    else{
        int t1 = CalculateStringDistance(strA, pABegin+1, pAEnd, strB, pBBegin, pBEnd);
        int t2 = CalculateStringDistance(strA, pABegin, pAEnd, strB, pBBegin+1, pBEnd);
        int t3 = CalculateStringDistance(strA, pABegin+1, pAEnd, strB, pBBegin+1, pBEnd);
        return min(t1, min(t2, t3)) + 1;
    }
}
```


### 3.4 从无头单链表中删除节点

```cpp
void DeleteRandomNode(node* pCurrent){
    Assert(pCurrent != NULL);
    node* pNext = pCurrent->next;
    if(pNext != NULL){
        pCurrent->data = pNext->data;
        pCurrent->next = pNext->next;
        delete pNext;
    }
}
```