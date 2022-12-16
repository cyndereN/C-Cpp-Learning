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