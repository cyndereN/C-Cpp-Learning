# 编程之美

## 第1章 游戏之乐 ———— 游戏中碰到的题目

### 1.1 让CPU占有率听你指挥

写一个程序，让用户来决定Windows任务管理器的CPU占用率
1. 50%，一条直线
2. 命令行参数，一条直线
3. 一个正弦曲线

```c

int main() {
    for (; ; )
    {
        for (int i = 0; i <9600000; i++) // 根据CPU产生差异
            ;
        Sleep(10);   // 接近windows的调度时间片
    }
    return 0;
}
```

```c
// 解放n值

const DWORD busyTIme = 10;            // 10ms
const DWORD int idleTime = busyTime;  // Same ratio will lead to 50% cpu usage

Int64 startTime = 0;

while(true){
    DWORD startTime = GetTickCount();
    // busy loop
    while ((GetTickCount() - startTime) <= busyTime>)
        ;
    
    // idle loop
    Sleep(idelTime);
}
```

```Cs
// 动态适应
static void MakeUsage(float level) {
    PerformanceCounter p = new PerformanceCounter("Processor", "% Processor Time", "_Total");

    while(true){
        if(p.NextValue() > level)
            System.Threading.Thread.Sleep(10);
    }
}
```


// 正弦曲线：把一条正弦曲线0-2π之间的弧度等分成200份进行抽样，计算每个抽样点的振幅
// 每隔300ms取下一个抽样点并让CPU工作对应振幅的时间


### 1.2 中国象棋将帅问题

3*3 格子，只用一个字节存储变量，输出所有A, B合法位置

1个8位字节可以表示2^8=256个值，所以用它前4个bit表示A、后4个表示B，4个bit能表示16个数字，已经足够了

```
BYTE i = 81;
while (i--){
    if(i/9 % 3 == i%9%3)    continue;
    printf("A=%d, B=%d\n", i/9+1, i%9+1);
}
```


```
struct{
    unsigned char a:4;
    unsigned char b:4;
} i;

for (i.a=1; i.a <= 9; i.a++)
    for (i.b =1; i.a <= b; i.b++)
        if(i.a%3 != i.b%3)
            printf("..");
```


### 1.3 烙饼排序

优化？
两次翻转即可把最大的翻到最下面，那么至多需要2(n-1)次————上界，m_nMaxSwap
如果操作+预计操作大于上界，则剪枝
nEstimate越大，剪枝条件越容易被满足
告诉“神仙”当前状态，他就能告诉你最少需要多少次翻转————下界，当前n个烙饼中，有m对相邻的烙饼半径不相邻，则至少需要m次（目前找到的最大下界是[15n/14]，也就是说如果有100个烙饼，那么我们至少需要15*100/14 = 108次才能翻好）


尽可能减小UpperBound, 增加LowerBound

```cpp
/****************************************************************/
//
// 烙饼排序实现
//
/****************************************************************/
class CPrefixSorting
{
public:

     CPrefixSorting()    
     {
          m_nCakeCnt = 0;
          m_nMaxSwap = 0;
     }

    ~CPrefixSorting()
    {
          if( m_CakeArray != NULL )
          {
               delete m_CakeArray;  
          }
          if( m_SwapArray != NULL )
          {
               delete m_SwapArray;  
          }
          if( m_ReverseCakeArray != NULL )
          {
               delete m_ReverseCakeArray;  
          }
          if( m_ReverseCakeArraySwap != NULL )
          {
               delete m_ReverseCakeArraySwap;  
          }
     }

     //
     // 计算烙饼翻转信息
     // @param
     // pCakeArray	存储烙饼索引数组
     // nCakeCnt	烙饼个数
     //
     void Run(int* pCakeArray, int nCakeCnt)
     {
          Init(pCakeArray, nCakeCnt);

          m_nSearch = 0;
          Search(0);
     }

     //
     // 输出烙饼具体翻转的次数
     //
     void Output()
     {
          for(int i = 0; i < m_nMaxSwap; i++)
          {
               printf("%d ", m_arrSwap[i]);
          }
		
          printf("\n |Search Times| : %d\n", m_nSearch);
          printf("Total Swap times = %d\n", m_nMaxSwap);
     }

private:

     //
     // 初始化数组信息
     // @param
     // pCakeArray	存储烙饼索引数组
     // nCakeCnt	烙饼个数
     //
     void Init(int* pCakeArray, int nCakeCnt)
     {
          Assert(pCakeArray != NULL);
          Assert(nCakeCnt > 0);

          m_nCakeCnt = nCakeCnt;

          // 初始化烙饼数组
          m_CakeArray = new int[m_nCakeCnt]; 
          Assert(m_CakeArray != NULL);
          for(int i = 0; i < m_nCakeCnt; i++)
          {
               m_CakeArray[i] = pCakeArray[i];
          }

          // 设置最多交换次数信息
          m_nMaxSwap = UpBound(m_nCakeCnt);

          // 初始化交换结果数组 
          m_SwapArray = new int[m_nMaxSwap + 1];
          Assert(m_SwapArray != NULL);

          // 初始化中间交换结果信息
          m_ReverseCakeArray = new int[m_nCakeCnt];
          for(i = 0; i < m_nCakeCnt; i++)
          {
               m_ReverseCakeArray[i] = m_CakeArray[i];
          }
          m_ReverseCakeArraySwap = new int[m_nMaxSwap];
     }
    
    
     //
     // 寻找当前翻转的上界
     //
     //
     int UpBound(int nCakeCnt)
     {
          return nCakeCnt*2;
     }

     //
     // 寻找当前翻转的下界
     //
     //
     int LowerBound(int* pCakeArray, int nCakeCnt)
     {
          int t, ret = 0;

          // 根据当前数组的排序信息情况来判断最少需要交换多少次
          for(int i = 1; i < nCakeCnt; i++)
          {
               // 判断位置相邻的两个烙饼，是否为尺寸排序上相邻的
               t = pCakeArray[i] - pCakeArray[i-1];
               if((t == 1) || (t == -1))
               {
               } 
               else
               {
                    ret++;
               }
          }
          return ret;
     }

     // 排序的主函数
     void Search(int step)
     {
          int i, nEstimate;

          m_nSearch++;

          // 估算这次搜索所需要的最小交换次数
          nEstimate = LowerBound(m_ReverseCakeArray, m_nCakeCnt);
          if(step + nEstimate > m_nMaxSwap)
               return;

          // 如果已经排好序，即翻转完成，输出结果
          if(IsSorted(m_ReverseCakeArray, m_nCakeCnt))
          {
               if(step < m_nMaxSwap)
               { 
                    m_nMaxSwap = step;
                    for(i = 0; i < m_nMaxSwap; i++)
                         m_arrSwap[i] = m_ReverseCakeArraySwap[i];
               }
               return;
          }

          // 递归进行翻转
          for(i = 1; i < m_nCakeCnt; i++)
          {
               Revert(0, i);
               m_ReverseCakeArraySwap[step] = i;
               Search(step + 1);
               Revert(0, i);
          }
     }
     //
     // true : 已经排好序
     // false : 未排序
     //
     bool IsSorted(int* pCakeArray, int nCakeCnt)
     {
          for(int i = 1; i < nCakeCnt; i++)
          {
               if(pCakeArray[i-1] > pCakeArray[i])
               {
                    return false;
               }
          }
          return true;
     }

     //
     // 翻转烙饼信息
     //    
     void Revert(int nBegin, int nEnd)
     {
          Assert(nEnd > nBegin);
          int i, j, t;

          // 翻转烙饼信息
          for(i = nBegin, j = nEnd; i < j; i++, j--)
          {
               t = m_ReverseCakeArray[i]; 
               m_ReverseCakeArray[i] = m_ReverseCakeArray[j];
               m_ReverseCakeArray[j] = t;
          }
     }

private:

     int* m_CakeArray;	// 烙饼信息数组
     int m_nCakeCnt;	// 烙饼个数
     int m_nMaxSwap;	// 最多交换次数。根据前面的推断，这里最多为
                          	// m_nCakeCnt * 2 
     int* m_SwapArray;	// 交换结果数组

     int* m_ReverseCakeArray;	// 当前翻转烙饼信息数组
     int* m_ReverseCakeArraySwap;	// 当前翻转烙饼交换结果数组
     int m_nSearch;	// 当前搜索次数信息
};
```

### 1.4 买书问题

### 1.5 快速找出故障机器

　有很多服务器存储数据，假设一个机器仅存储一个标号为ID的记录，假设机器总量在10亿以下且ID是小于10亿的整数，假设每份数据保存两个备份，这样就有两个机器存储了同样的数据。

问题是：1.假设在某个时间得到一个数据文件ID的列表，是否能快速地找出表中仅出现一次的ID？即快速找出出现故障的机器存储的数据ID。

　　　　2.如果有两台机器出现故障呢？（假设存储同一份数据的两台机器不会同时出现故障，即列表中缺少的是两个不等的ID）

 

给出了4种解法思路

解法一：

　　最传统的比较列表，需要遍历整个列表，记录每个ID出现的次数，最后输出只出现一次的ID，时间复杂度O(n)，空间复杂度也为O(n)，如果数据量太大，实际运算效率会很低下。

解法二：

　　优化存储空间，在很多数据中，大部分出现次数都是2，出现故障的机器为少数，通过Hash Table，Key值为机器ID，Value值为出现次数。遍历列表，遇到ID，就将ID的Value值加1。Value值为2的话，删除这个Key。最后Hash表中剩下的就是出故障的机器ID。

　　最好情况下空间复杂度为O(1)，最坏仍为O(n)。

解法三：

　　前两种方法已经将空间复杂度降到了O(n)，如果在想降到常数级，就需要换一种思路，不用遍历列表的这种方法。

如果能只用一个变量记录遍历列表的结果，那么空间复杂度可将为O(1)。

　　x(N)=ID_Lost。考虑到列表中，只有一个ID出现了1次，其他都是2次，可以用到计算机语言里面的异或(XOR、⊕)。

A⊕A=0

A⊕0=A

　　最终x(n)=List[0]⊕List[1]⊕List[2]⊕……⊕List[n]  的运算结果即为只出现一次的ID号，空间复杂度为1。

　　但如果有2个ID只出现了一次，假设出现一次的ID为A,B，x(n)的为A⊕B，仍无法确定AB的值。

　　异或之后的二进制值，某一位为1的话，可以推断出，AB2个数中，这个位置，一个是0，一个是1。我们将所有ID，分为2类，一类这位上为1，一类这位上为0。这2类个包含了AB中的一个，使用2个变量，遍历列表做异或处理，即可找出A和B的值。

解法四：

　　将问题进行扩展，现在故障机器的ID相同，既2台存储相同数据的机器同时嗝屁了。运用一些数学上的知识，数学中有不变量，在这里，事先预订的整数ID集合中，所有的ID相加可以得到一个不变量。将现在的ID集合相加，用不变量减去现在的ID集合的和，即可得到丢失数据ID的。时间复杂度为O(n)，空间复杂度O(1)。

　　如果这2台机器ID不同，我们只是得到了他们的ID之和，x+y=a，并不能知道他们到底是多少。可以再构建一个等式，构成一个方程，解方程组，得出x和y的值。同样使用不变量的概念，比如所有ID的乘积，最后得出来xy=b，解出x，y的值。

 

 

总结：

　　在算法设计是一个慢慢发展过程中，开始的时候可能只是想出了最普通的一个解法，效率不高，但能解决问题。做到这一步之后，想要更进一步，就需要在时间复杂度或者空间复杂度方面做一些优化。还可以根据题中的一些条件，想一些可以用计算机方式解决的方法，如异或、与、正则表达。还可以用数学的思想来看看问题有没有解决的办法。

```c
#include "stdio.h"

int main(){
    int List[]={1,2,3,5,6,7,8,9,0,1,2,3,4,5,6,8,9};//ȱ0,7,4 
    int t;
    int length=sizeof(List)/sizeof(List[0]);
    printf("%d\n",length);

    for(int i=0;i<length;i++){
    t=0;
        for(int j=0;j<length;j++)
            if(List[i]==List[j])
                t=t+1;
    if(t!=2)
        printf("%d\n",List[i]);
    }
}
```


### 1.6 饮料供货

空间复杂度O(N*V)(可降为O(V)) 时间复杂度O(V*N*Max(Ci))
```cpp
int Cal(int V, int T){
     opt[0][T] = 0;     // T为饮料种类
     for (int i = 1; i <= V ; i++){ // 边界条件
          opt[i][T] = -INF;
     }

     for(int j = T-1; j >= 0; j--){
          for(int i = 0; i<=V; i++){   
               opt[i][j] = -INF;

               for(int k=0; k<= C[j]; k++){  // 遍历第j种饮料选取数量k
                    if(i <= k*V[j])     break;
                    int x = opt[i -k*V[j]][j+1];
               }

               if( x!= -INF){
                    x += H[j]*k;
                    if(x>opt[i][j])     opt[i][j] = x;
               }
          }
     }

     return opt[V][0];
}
```

```cpp
int opt_num[MAXV + 1][MAXT + 1];
// 备忘录法
int Cal1(int V, int type) {
    if (type == T) {
        if (V == 0)
            return 0;
        else
            return -INF;
    }
    if (V < 0)
        return -INF;
    else if (V == 0)
        return 0;
    else if (opt[V][type] == -1)
        return opt[V][type];

    int ret = -INF;
    for (int i = 0; i <= c[type]; ++i) {
        int temp = Cal1(V - i * v[type], type + 1);
        if (temp != -INF) {
            temp += i * h[type];
            if (temp > ret) {
                opt_num[V][type] = i;
                ret = temp;
            }
        }
    }
    return opt[V][type] = ret;
}

```

### 1.7 光影切割问题 
假设N条直线，M个交点，分成的区域数目 = N+M+1
只需查询每条直线是否与其他N-1条直线有交点。初始化的复杂度为O(N^2)，每次查询的时间复杂度为O(|Intersect|)。
如果在初始化之后对所有交点按x轴进行排序，则复杂度为O(N^2+|Intersect|\*log|Intersect|)，后面为排序时间，之后可以用二分查找，每次查询的时间复杂度将为O(log|Intersect|)
如果查询比较少，可以求逆序数，O(N^2)，可以用分治法将时间复杂度降为O(N\*logN)

### 1.8 小飞的电梯调度算法
本质是一个优化问题。
最简单解法O(N^2) 1-N层枚举x循环，分别计算每个x楼层的总数

从第一层开始考察，N1为目的楼层在第i层楼以下的乘客数，N2为在第i层楼的乘客数，N3为之上的乘客数。
在第i-1层停，需多爬N2+N3-N1层，在i+1层停，需多爬N1+N2-N3层。所以，当N1>N2+N3，在i-1，N1+N2<N3，在i+1层最好，反之i
```cpp
int nPerson[]; // nPerson[i]表示到第i层的乘客数目
int nMinFloor, nTargetFloor;
int N1, N2, N3;

nTargetFloor = 1;
mMinFloor = 0;

for (N1 = 0, N2 = nPerson[1], N3 = 0, i = 2; i <= N; i++){
  N3 += nPerson[i];
  nMinFloor += nPerson[i]*(i-1);
}

for (i=2 ; i<=N ; i++){
  if(N1+N2<N3){
    nTargetFloor = i;
    nMinFloor += (N1+N2-N3);
    N1+=N2;
    N2 = nPerson[i];
    N3 -= nPerson[i];
  }
  else
    break;
}

return (nTargetFloor, nMinFloor)
```
### 1.9 高效安排见面会
不同的k个见面小组如果有一个人同时感兴趣，那么就给他们连起来，最小着色问题。G(E,V)
解法1，对顶点1分配颜色1，然后枚举其他所有颜色可能O((n-1)^n)，验证一种颜色的时间复杂度是O(n^2)，共O((n-1)^n\*n^2)
解法2，对图尝试k种着色，首先设为1，看看有没有合适方案，在逐渐提高K

### 1.10 双线程下载
下载的同时写入磁盘
```cpp
//---------------------API------------------------------


//downloads a block from Internet sequentially in each call
//return true, if the entire file is downloaded, otherwise false.
bool GetBlockFromNet(Block* out_block);

//writes a block to hard disk
bool WriteBlockToDisk(Block* in_block);
  
class Thread
{
public:
    Thread(void (*work_func)());
    ~Thread();
    void Start();
    void Abort();
};
 
class Semaphore
{
public:
    Semaphore(int count,int max_count);
    ~Semaphore(); 
    // consume a signal(count--), block current thread if count == 0
    void Unsignal();
    // raise a signal(count++)
    void Signal();
};
 
class Mutex
{
public:
    // block thread until other threads realease the mutex
    WaitMutex();
    // rlease mutex to let other thread wait for it
    ReleaseMutex();
};
//----------------------------------------------------
```
分析与解法：

1.什么时候才算完成任务？

下载完毕并且完全存储到硬盘上，两个线程才能正常终止。

2.希望两个线程能同时工作，又不发生冲突，用什么方法？

使用Mutex（互斥量），下载时不能存储所以弃用。

使用Semaphore（信号量）是更好的选择。

3.下载与存储的必要条件

buffer满的时候和所有内容下载完毕，应该停止下载。

buffer为空时，没必要运行存储线程。 
```cpp
#define BUFFER_COUNT 100  //定义数据队列中数据块的数目。
//每一个数据块将是下载线程和存储线程操作的基本的单元
BLOCK g_buffer[BUFFER_COUNT];//数据缓冲区队列
 
Thread g_ThreadA(ProcA);//下载线程
Thread g_ThreadB(ProcB);//存储线程
//信号量，表示现在在数据队列中已经存放满数据的数据块的数量
Semaphore g_seFull(0,BUFFER_COUNT);
//信号量，表示现在在数据队列中空数据块的数量
Semaphore g_seEmpty(BUFFER_COUNT,BUFFER_COUNT);
bool g_downloadComplete = false;
int in_index = 0;//表示当前下载线程正在处理的数据块的编号
int out_index = 0;//表示当前存储线程正在处理的数据块的编号
 
void main()
{
     g_ThreadA.start();//启动下载线程
     g_ThreadB.start();//启动存储线程
     Wait();
}
 
//下载线程的工作函数
void ProcA()
{
     while(true)
     {
           //申请一个空的数据块的资源
          g_seEmpty.Unsignal();  
          //申请到空的数据块，向in_index指向的BLOCK下载数据
          g_downloadComplete = GetBlockFromNet(g_buffer + in_index);
          //in_index更新
          in_index = (in_index + 1) % BUFFER_CONUT;  
          g_seFull.Signal();//报告又有一个新的数据块已经下载完毕，可以指向写入操作...
         if(g_downloadComplete)
                break;
     }
}
 
//存储线程的工作函数
void ProcB()
{
     while(true)
     {
           //申请一个满的数据块的资源
          g_seFull.Unsignal();  
          //申请到满的数据块，从out_index指向的BLOCK获取数据，写入Disk。
          WriteBlockToDisk(g_buffer + out_index);
          //out_index更新
          out_index = (out_index + 1) % BUFFER_CONUT;  
          g_seEmpty.Signal();//报告又有一个新的数据块已经写入完毕，可以下载覆盖其数据...
         if(g_downloadComplete && out_index == in_index)
               break;
     }
}
```
### 1.11 NIM(1) 一排石头的游戏
先取者必胜

### 1.12 NIM(2) 游戏分析

(x, x)是安全局面
摆放方法为(1,...,1) 若1为偶数个则先拿者输，若1为奇数个则先拿者赢
摆放方法为(1,...,x) 先拿者必赢
每次拿都会改变XOR(...)的值(0->1,1->0)
若赢只需XOR(...) = 0即可
M为奇数时无论怎么分堆，先拿者必赢

### 1.13 NIM(3) 两堆石头的游戏
类似计算质数时的筛法
发现所有不安全局面<1,2><3,5><4,7><6，10>...
这些数合起来就是所有正整数的集合，他们的差的绝对值也是。
总结为一个通项公式an=\[a\*n] bn=\[b\*n]
a = (1+sqrt(5))/2
b = (3+sqrt(5))/2

### 1.14 连连看游戏设计

自动机模型最适合描述游戏设计

### 1.15 构造数独

先生成完整合法的解，再反过来删除一些数字

经典深度优先搜索，从(0, 0)开始，对于没有处理过的格子，调用GetValidValueList(coCurrent)来获得当前格子可能的取值选择，并从中取一个为当前格子的取值，接着搜索下一个。若没有，则回溯，修改前一个格子的取值，直到所有格子都找到可行取值为止


还有一种，随机将{1, ..., 9}映射到{a, ..., i}，把棋盘分9大块，每大块9小块，中间那块按a,b,c第一行，d,e,f第二行, g,h,i第三行排列，之后通过置换行的办法横向拓展，即abc一行被移到了另外两个矩阵中不相同的行上，def，ghi两行也一样。接着置换列作纵向扩展，即可得到合法解。

### 1.16 24点游戏

1. 穷举法：不包括括号，4! x 4^3 = 1536；包括括号4! x 4^3 x 5 = 7680种；递归，将给定的4个数放入数组array中，将其作为参数传入函数f中

```c
f(Array){
     if (Array.Length < 2){
          if (得到的结果为24)   输出表达式
          else 输出无法构造符合要求的表达式
     }

     foreach(从数组中任取两个数)
     {
          foreach(运算符(+, -, x, /))
          {
               1. 计算该组合在此运算符下的结果
               2. 将该组合中的两个数从原数组中移除，并将步骤1的计算结果放入数组
               3. 对新数组递归调用f，如果找到一个表达式则返回
               4. 将步骤1的计算结果移除，并将该组合中的两个数重新放回数组中对应的位置
          }
     }
}
```
使用动态规划实现，给定4个数：A={a0，a1，a2，a3}。采用4位二进制表示集合，当且仅当ai在某一个子集中时，该子集所代表的二进制数对应的第i位为1，否则为0，比如A1={a1，a2，a3}，则1110代表A1，总共需要1到2^n-1表示所有的子集，包括A自身。所以不妨设S表示所有子集所有的运算结果。比如：s[3]表示A3={a0，a1}的运算，s[3]中存储{a0+a1、a0-a1、a1-a0、a0*a1、a0/a1、a1/a0}。s[1]={a0}、s[2]={a1}、s[4]={a2}、s[8]={a3}。对于{a0,a1,a2}—>{a0}+{a1，a2}、{a1}+{a0，a2}、{a2}+{a0，a1}，即：s[1]中元素与s[6]中元素进行加、减、乘、除六种的运算，结果存储在s[7]中，同样s[2]与s[5]，s[3]与s[4]，这样就完成了{a0,a1,a2}所有的可能组合表达式的运算。其它的依次类推。自底向上计算，s[15]中存储{a0，a1，a2，a3}所有可能的组合表达式的结果，只要遍历s[15]中结果为24的表达式将其输出，就可以找到所有满足结果为24的表达式。具体过程详见编程之美，这里只是讲解程序是如何实现的。

game24.h
```cpp
#pragma once
#include<iostream>
#include<vector>
#include<string>
using namespace std;

class Game
{
public:
	void insert(int x);
	void start();
	void Find(int k);
	void Fork(int a,int b);
	void show();
private:
	vector<int> c;
	vector<vector<double> > s;
	vector<vector<string> > result;
};
```

game24.cpp
```
#include"stdafx.h"
#include"game24.h"
#include<iostream>
#include<vector>
#include<stdlib.h>
#include<math.h>
using namespace std;

void Game::insert(int x)
{
	c.push_back(x);
}
void Game::start()
{
	int n=c.size();
	int m=pow(2,(double)n);
	s.resize(m);//其中s[0]不使用
	result.resize(m);
	for(int i=0;i<n;i++)
	{
		char buffer[20];
		s[pow(2,(double)i)].push_back(c[i]);
		_itoa_s(c[i],buffer,10);
		result[pow(2,(double)i)].push_back(buffer);
	}
	for(int i=1;i<m;i++)
		Find(i);
}
void Game::Find(int k)
{
	if(!s[k].empty())
		return ;
	for(int i=1;i<k;i++)
	{
		int t=i&k;
		if((t==i)&&(i<k-i))//i&k=i时,i才为k的子集，比如，k=0101，只有i=0001、0100才是其子集k=0101
			Fork(i,k-i);   //代表A5={a2，a0}其子集只有{a2}、{a0}，其它不满足
	}
}
void Game::Fork(int a,int b)
{
	string str;
	int n1=s[a].size();
	int n2=s[b].size();
	for(int i=0;i<n1;i++)
		for(int j=0;j<n2;j++)
		{
			s[a+b].push_back(s[a][i]+s[b][j]);
			str='('+result[a][i]+'+'+result[b][j]+')';
			result[a+b].push_back(str);


			s[a+b].push_back(s[a][i]-s[b][j]);
			s[a+b].push_back(s[b][j]-s[a][i]);
			str='('+result[a][i]+'-'+result[b][j]+')';
			result[a+b].push_back(str);
			str='('+result[b][j]+'-'+result[a][i]+')';
			result[a+b].push_back(str);



			s[a+b].push_back(s[a][i]*s[b][j]);
			str='('+result[a][i]+'*'+result[b][j]+')';
			result[a+b].push_back(str);


			if(s[b][j]!=0)
			{
				s[a+b].push_back(s[a][i]/s[b][j]);
				str='('+result[a][i]+'/'+result[b][j]+')';
			    result[a+b].push_back(str);
			}
			if(s[a][i]!=0)
			{
				s[a+b].push_back(s[b][j]/s[a][i]);
				str='('+result[b][j]+'/'+result[a][i]+')';
			    result[a+b].push_back(str);
			}
		}
}
void Game::show()
{
	start();
	int m=c.size();
	int k=pow(2,(double)m)-1;
	int n=s[k].size();
	vector<string> s1;
	for(int i=0;i<n;i++)
		if(fabs(s[k][i]-24)<1E-6)
		{
			if(s1.empty())
			{
            cout<<result[k][i]<<"=24"<<endl;
			s1.push_back(result[k][i]);
			cout<<endl;
			}
			int n1=s1.size();
			for(int j=0;j<n1;j++)
			{
				if(result[k][i]!=s1[j])
				{
				cout<<result[k][i]<<"=24"<<endl;
				cout<<endl;
				}
			}
		}
}
```

Beauty-24dynamic.cpp
```cpp
// Beauty-24dynamic.cpp : 定义控制台应用程序的入口点。
//
//编程之美：24点游戏，分治算法和动态规划思想
#include "stdafx.h"
#include"game24.h"
#include<iostream>
#include<vector>
using namespace std;
int _tmain(int argc, _TCHAR* argv[])
{

	Game g;
	cout<<"Input numbers:"<<endl;
	for(int i=0;i<4;i++)
	{
		int x;
		cin>>x;
		g.insert(x);
	}
	g.show();
	return 0;
}

```


### 1.17 俄罗斯方块


### 1.18 扫雷游戏

