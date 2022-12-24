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
告诉“神仙”当前状态，他就能告诉你最少需要多少次翻转————下界，当前n个烙饼中，有m对相邻的烙饼半径不相邻，则至少需要m次

尽可能减小UpperBound, 增加LowerBound

```cpp
class CPrefixSorting{
    CPrefixSorting(){
        m_nCakeCnt = 0;
        m_nMaxSwap = 0;
    }
};
```
