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



### 3.5 最短摘要的生成
先简化和抽象问题，在最简单算法的基础之上找出可能的简化方案，进而降低算法的复杂度。
不断深入分析问题，逐步找出更加可行的方案，直到找到最优解。

### 3.6 编程判断两个链表是否相交
假设链表不带环

解法1：判断链表1的每一个节点是否在第二个链表中O(length1*length2)

解法2：利用计数方法，对第一个链表节点地址进行hash排序，建立hash表，然后针对第二个链表进行查找。O(length1+length2)，但是需要O（length1）的空间

解法3：转化为已知问题，把第一个链表的尾节点指向第二个链表的头节点，然后判断第二个链表是否有环。O(length1+length2)

解法4：抓住要点：如果相交，那么他们之后的节点也是共有的->最后一个节点相同。O(length1+length2) 如果使用C++链表则为O(1)


### 3.7 队列中取最大值操作问题

队列有三个操作：EnQueue(v)、DeQueue、MaxElement。其中EnQueue(v)将v加入队列，DeQueue删除队首元素并返回该元素，MaxElement返回队列中的最大元素。请设计一种数据结构和算法，使得MaxElement操作的时间复杂度尽可能地低。


方法1：需要遍历队列中的所有元素，从而得到最大值，时间复杂度为O(N)。或者空间换时间，用一个变量保存最大值，每次插入元素时，如果比最大值大，则更新最大值。时间复杂度为O(1)。但是这样做如果最大值被deque了，就需要重新遍历队列找到最大值，时间复杂度为O(N)。

方法2：使用一个堆来保存队列中的数据。用两个指针保存队列头部和尾部的地址，堆中每个元素保存下一个元素的地址(对应于队列中的位置)。EnQueue和DeQueue操作的时间复杂度是O(logN)，MaxElement操作的时间复杂度是O(1)。

方法3：用两个栈来实现队列。由于栈只在一端进行操作，可以用一个数组(或者栈)保存当前栈的最大值。再用两个栈实现队列。

```cpp
// 用两个栈实现O(1)返回栈的最大值
template < typename T >
class max_stack {
	stack<T> sta;
	stack<T> max_sta;

public:
	void push(T &value)
	{
		if(sta.empty()) {
			sta.push(value);
			max_sta.push(value);
		}
		else {
			sta.push(value);
			max_sta.push(max(value, max_sta.top()));
		}
	}

	void pop()
	{
		if(sta.empty()) {
			throw string("empty stack");
		}

		sta.pop();
		max_sta.pop();
	}

	T top()
	{
		if(sta.empty()) {
			throw string("empty stack");
		}

		return sta.top();
	}

	T max()
	{
		if(sta.empty()) {
			return numeric_limits<T>::min();
		}
		else {
			return max_sta.top();
		}
	}
};

// 用两个栈实现O(1)返回队列的最大值
template < typename T >
class max_queue {
	max_stack<T> sta1;
	max_stack<T> sta2;

public:
	void push(T &value)
	{
		sta1.push(value);
	}

	void pop()
	{
		if(!sta2.empty()) {
			sta2.pop();
		}
		else {
			if(sta1.empty()) {
				throw string("empty queue");
			}

			T t;
			while(!sta1.empty()) {
				t = sta1.top();
				sta1.pop();
				sta2.push(t);
			}

			sta2.pop();
		}
	}

	T max()
	{
		return max(sta1.max(), sta2.max());
	}
};
```

### 3.8 二叉树中节点最大距离

把二叉树当成图。相距最远的一定是叶子节点和叶子节点或者叶子结点和根节点。

递归找左右子树的最大距离，直到叶子节点，然后返回最大距离。

```cpp

int nMaxLen = 0;

// 寻找树中最长的两端距离

void FindMaxLen(Node* pRoot){
    if(pRoot == NULL){
        return 0;
    }
    int nLeftLen = FindMaxLen(pRoot->left);
    int nRightLen = FindMaxLen(pRoot->right);
    nMaxLen = max(nMaxLen, nLeftLen + nRightLen);
    return max(nLeftLen, nRightLen) + 1;
}
```


### 3.9 重建二叉树

前序：当前，前序（左），前序（右），类似深度优先搜索（DFS）算法；层次遍历类似广度优先（BFS）算法
中序：中序（左），当前，中序（右）
后序：后序（左），后序（右），当前

给定 先序+中序 or 后序+中序 可以唯一确定一颗二叉树
而 先序+后序 不能
	  A
	 /
	B
前序遍历： AB, 后序遍历： BA
	A
	 \
	  B
前序遍历： AB, 后序遍历： BA

解法1：
```cpp
public class Solution {
    public TreeNode reConstructBinaryTree(int [] pre,int [] in) {
        TreeNode root=buildTree(pre,0,pre.length-1,in,0,in.length-1);
        return root;
    }
    public TreeNode buildTree(int []pre,int startPre,int endPre,int []in,int startIn,int endIn){
        if(startPre>endPre||startIn>endIn){
            return null;
        }
        //前序遍历先访问根结点，所以前序遍历序列的首个元素即为根结点。
        TreeNode root=new TreeNode(pre[startPre]);
        //在中序遍历序列中寻找根节点的位置，并将序列分为左右子树
        for(int i=startIn;i<=endIn;i++){
            if(in[i]==pre[startPre]){
                int leftcount=i-startIn;//求左子树结点个数
                //在左子树序列中寻找根的左孩子结点
                root.left = buildTree(pre,startPre+1,startPre+leftcount,in,startIn,i-1);
                //在右子树序列中寻找根的右孩子结点
                root.right = buildTree(pre,startPre+leftcount+1,endPre,in,i+1,endIn);
                break;
            }
        }
        return root;
    }
}
```